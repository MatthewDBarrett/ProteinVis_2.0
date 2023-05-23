/**********************************************************************************
 * Multiple Match
 *
 * Used to align groups of molecules to each other, both in rotation and translation. 
 * Multiple methods for creating different sorting orders are provided.
 * 
 * 0 - Global Sorting
 * 1 - Local Sorting
 * 2 - Sort by Rank
 * ________________________________________________________________________________
 *
 * This file is part of the ProteinVis project.
 *
 * Author:			Nico Pietroni
 *
 * Organisation:	University of Technology Sydney
 *
 * ProteinVis. is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * GNU General Public License V3, 29 June 2007.
 *
 * ProteinVis. is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * <https://www.gnu.org/licenses/gpl-faq.html/>
 *
 * For commercial licensing inquiries and restrictions, please contact either:
 * matthew.barrett@uts.edu.au
 * nico.pietroni@uts.edu.au
 **********************************************************************************/

#ifndef MULTIPLE_MATCH
#define MULTIPLE_MATCH

#include <vector>
#include "point_match.h"

inline double Distance(const std::vector<double>& P0,
    const std::vector<double>& P1)
{
    assert(P0.size() == 3);
    assert(P1.size() == 3);
    double XDiff = P0[0] - P1[0];
    double YDiff = P0[1] - P1[1];
    double ZDiff = P0[2] - P1[2];
    //return sqrt(XDiff*XDiff+YDiff*YDiff+ZDiff*ZDiff);
    return(XDiff * XDiff + YDiff * YDiff + ZDiff * ZDiff);
}

class MultipleMatch
{

    struct Trasform
    {
        Eigen::Matrix3d R;
        Eigen::Vector3d T;
        int FixP, MovP;
        double Err;

        Trasform(const Eigen::Matrix3d& _R,
            const Eigen::Vector3d& _T,
            int _FixP, int _MovP, double _Err)
        {
            R = _R;
            T = _T;
            FixP = _FixP;
            MovP = _MovP;
            Err = _Err;
        }

        inline bool operator <(const Trasform& _T1)const
        {
            assert(FixP >= 0);
            assert(MovP >= 0);
            return (Err < _T1.Err);
        }

        Trasform()
        {
            R.setIdentity();
            T = Eigen::Vector3d(0, 0, 0);
            FixP = -1;
            MovP = -1;
            Err = -1;
        }
    };

    //the indexed troasform
    std::vector<std::vector<Trasform> > TransMatrix;
    std::vector<std::vector<std::vector<double > > > PointConfig;

    //the sorted ones
    std::vector<std::vector<Trasform> > SortedTrasnf;

    //sorted locally
    std::vector<std::vector<Trasform> > SortedDepTrasnf;

    //sorted by rank
    std::vector<Trasform> SortedRankTrasnf;

    std::vector<double > Ranking;

    //sorted by
    std::vector<Trasform> SortedPrio;

    void InitSortFromFirst()
    {
        //PointConfig=_PointConfig;
        int numConf = PointConfig.size();

        //allocate matrix (numConf X numConf)
        TransMatrix.clear();
        TransMatrix.resize(numConf, std::vector<Trasform>(numConf));

        //compute rigid match
        for (size_t i = 0; i < PointConfig.size(); i++)
            for (size_t j = 0; j < PointConfig.size(); j++)
            {
                if (i == j)
                {
                    TransMatrix[i][j].FixP = i;
                    TransMatrix[i][j].MovP = j;
                    TransMatrix[i][j].Err = 0;
                }
                else
                {
                    //same number of vertices
                    assert(PointConfig[i].size() == PointConfig[j].size());
                    Eigen::Matrix3d R;
                    Eigen::Vector3d T;
                    PointMatch::ComputeLeastSquaresRigidMotion(PointConfig[i], PointConfig[j], R, T);
                    TransMatrix[i][j].FixP = i;
                    TransMatrix[i][j].MovP = j;
                    TransMatrix[i][j].R = R;
                    TransMatrix[i][j].T = T;
                    TransMatrix[i][j].Err = ComputeError(PointConfig[i], PointConfig[j], R, T);

                }
            }

        //then sort them considering the distance
        SortedTrasnf.clear();
        for (size_t i = 0; i < TransMatrix.size(); i++)
        {
            //copy the entire row
            std::vector<Trasform> CurrTrans = TransMatrix[i];

            //one transform with respect to others
            assert(CurrTrans.size() == PointConfig.size());

            //then sort
            std::sort(CurrTrans.begin(), CurrTrans.end());

            //check consistency
            assert(CurrTrans[0].T == Eigen::Vector3d(0, 0, 0));
            assert(CurrTrans[0].R == Eigen::Matrix3d::Identity());
            assert(CurrTrans[0].Err == 0);
            assert(CurrTrans[0].FixP == (int)i);
            assert(CurrTrans[0].MovP == (int)i);

            //then copy
            SortedTrasnf.push_back(CurrTrans);
        }
    }

    void InitBestSequence(int Index)
    {
        assert(Index >= 0);
        assert(Index < (int)SortedDepTrasnf.size());
        assert(SortedDepTrasnf[Index].size() == 0);

        //first inset the configuration itselt
        SortedDepTrasnf[Index].resize(SortedDepTrasnf[Index].size() + 1);
        SortedDepTrasnf[Index][0].FixP = Index;
        SortedDepTrasnf[Index][0].MovP = Index;
        SortedDepTrasnf[Index][0].Err = 0;

        std::vector<bool> HasInserted(PointConfig.size(), false);
        HasInserted[Index] = true;

        bool found = true;
        while (found)
        {
            Trasform currTrans = SortedDepTrasnf[Index].back();

            int LastIds = currTrans.MovP;

            //get the current one
            std::vector<std::vector<double > > TargetPoint = PointConfig[LastIds];

            //then transform
            PointMatch::ApplyTrasformRigidMatch(TargetPoint, currTrans.R, currTrans.T);

            found = false;
            double minErr = std::numeric_limits<double>::max();
            Trasform BestTrans;
            for (size_t j = 0; j < PointConfig.size(); j++)
            {
                if (HasInserted[j])continue;

                //then compute the translation wrt the leas one
                Eigen::Matrix3d R;
                Eigen::Vector3d T;
                PointMatch::ComputeLeastSquaresRigidMotion(TargetPoint, PointConfig[j], R, T);
                double Err = ComputeError(TargetPoint, PointConfig[j], R, T);

                if (Err > minErr)continue;

                minErr = Err;
                BestTrans.FixP = LastIds;
                BestTrans.MovP = j;
                BestTrans.Err = minErr;
                BestTrans.T = T;
                BestTrans.R = R;
                found = true;
            }
            if (found)
            {
                int MovIndex = BestTrans.MovP;
                assert(!HasInserted[MovIndex]);
                HasInserted[MovIndex] = true;
                SortedDepTrasnf[Index].push_back(BestTrans);
            }
        }
    }

    void InitSortStepByStep()
    {
        //PointConfig=_PointConfig;
        //int numConf=PointConfig.size();

        SortedDepTrasnf.clear();
        SortedDepTrasnf.resize(PointConfig.size());
        for (size_t i = 0; i < PointConfig.size(); i++)
            InitBestSequence(i);
    }

    void InitSortedByRank()
    {
        SortedRankTrasnf.clear();

        assert(Ranking.size() == PointConfig.size());

        //sort by rank
        std::vector<std::pair<double, int> > RankIndex;
        for (size_t i = 0; i < Ranking.size(); i++)
            RankIndex.push_back(std::pair<double, int>(Ranking[i], i));

        std::sort(RankIndex.begin(), RankIndex.end());
        //higher rank first
        std::reverse(RankIndex.begin(), RankIndex.end());

        //        for (size_t i=0;i<RankIndex.size();i++)
        //        {
        //            std::cout<<"Label:"<<RankIndex[i].second<<" Rank:"<<RankIndex[i].first<<std::endl;
        //        }

                //initialize by rank
        SortedRankTrasnf.clear();
        SortedRankTrasnf.resize(PointConfig.size());

        //sort the first one
        SortedRankTrasnf[0].Err = 0;
        SortedRankTrasnf[0].FixP = RankIndex[0].second;
        SortedRankTrasnf[0].MovP = RankIndex[0].second;

        //SortedRankTrasnf.push_back()
        for (size_t i = 1; i < RankIndex.size(); i++)
        {
            Trasform PrevTrans = SortedRankTrasnf[i - 1];
            SortedRankTrasnf[i].FixP = PrevTrans.MovP;
            SortedRankTrasnf[i].MovP = RankIndex[i].second;

            //get the previous
            std::vector<std::vector<double > > TargetPoint = PointConfig[PrevTrans.MovP];

            //then transform
            PointMatch::ApplyTrasformRigidMatch(TargetPoint, PrevTrans.R, PrevTrans.T);

            Eigen::Matrix3d R;
            Eigen::Vector3d T;

            //get current
            std::vector<std::vector<double > > MovPoint = PointConfig[RankIndex[i].second];
            PointMatch::ComputeLeastSquaresRigidMotion(TargetPoint, MovPoint, R, T);
            double Err = ComputeError(TargetPoint, MovPoint, R, T);

            SortedRankTrasnf[i].Err = Err;
            SortedRankTrasnf[i].T = T;
            SortedRankTrasnf[i].R = R;
        }

        //        for (size_t i=0;i<SortedRankTrasnf.size();i++)
        //        {
        //            std::cout<<"Label 1 :"<<SortedRankTrasnf[i].MovP<<std::endl;
        //            std::cout<<"Error :"<<SortedRankTrasnf[i].Err<<std::endl;
        //        }
    }

public:

    double ComputeError(const std::vector<std::vector<double > >& PFix,
        const std::vector<std::vector<double > >& PMov,
        const Eigen::Matrix3d& R, const Eigen::Vector3d& T)
    {
        std::vector<std::vector<double > > PTest = PMov;
        assert(PFix.size() == PMov.size());
        PointMatch::ApplyTrasformRigidMatch(PTest, R, T);
        double Err = 0;
        for (size_t i = 0; i < PTest.size(); i++)
            Err += Distance(PTest[i], PFix[i]);

        return Err;
    }

    //for each point cloud, for each vertex X,Y,Z
    void InitMatches(const std::vector<std::vector<std::vector<double > > >& _PointConfig,
        const std::vector< double >& _Ranking)
    {
        PointConfig = _PointConfig;
        Ranking = _Ranking;

        InitSortFromFirst();

        InitSortStepByStep();

        InitSortedByRank();
    }

    //for each point cloud, for each vertex X,Y,Z
    void InitMatches(const std::vector<std::vector<std::vector<double > > >& _PointConfig)
    {
        PointConfig = _PointConfig;

        InitSortFromFirst();

        InitSortStepByStep();
    }

    //return the index-sorted from the reference Ref index
    void GetSortedSequencePoint(const size_t RefIndex,
        const size_t CurrIndex,
        size_t& CurrLabel, double& currError,
        std::vector<std::vector<double > >& TransfPoint,
        int queryMode)
    {
        assert((queryMode == 0) || (queryMode == 1) || (queryMode == 2));

        Trasform currTrans;
        switch (queryMode)
        {
        case 0:
            assert(RefIndex < SortedTrasnf.size());
            assert(CurrIndex < SortedTrasnf[RefIndex].size());

            currTrans = SortedTrasnf[RefIndex][CurrIndex];
            assert(currTrans.FixP == (int)RefIndex);

            CurrLabel = currTrans.MovP;
            currError = currTrans.Err;

            //get the point cloud
            TransfPoint = PointConfig[currTrans.MovP];
            break;

        case 1:
            assert(RefIndex < SortedDepTrasnf.size());
            assert(CurrIndex < SortedDepTrasnf[RefIndex].size());

            currTrans = SortedDepTrasnf[RefIndex][CurrIndex];
            //assert(currTrans.FixP==(int)RefIndex);

            CurrLabel = currTrans.MovP;
            currError = currTrans.Err;

            //get the point cloud
            TransfPoint = PointConfig[currTrans.MovP];
            break;

        default:
            assert(RefIndex < SortedRankTrasnf.size());

            currTrans = SortedRankTrasnf[RefIndex];

            CurrLabel = currTrans.MovP;
            currError = currTrans.Err;

            //get the point cloud
            TransfPoint = PointConfig[currTrans.MovP];
            break;
        }

        //then transform
        PointMatch::ApplyTrasformRigidMatch(TransfPoint, currTrans.R, currTrans.T);
    }
};

#endif
