#ifndef MULTIPLE_MATCH
#define MULTIPLE_MATCH

#include <vector>
#include "point_match.h"

inline double Distance(const std::vector<double> &P0,
                       const std::vector<double> &P1)
{
    assert(P0.size()==3);
    assert(P1.size()==3);
    double XDiff=P0[0]-P1[0];
    double YDiff=P0[1]-P1[1];
    double ZDiff=P0[2]-P1[2];
    return sqrt(XDiff*XDiff+YDiff*YDiff+ZDiff*ZDiff);
}

class MultipleMatch
{

    struct Trasform
    {
        Eigen::Matrix3d R;
        Eigen::Vector3d T;
        int FixP,MovP;
        double Err;

        Trasform(const Eigen::Matrix3d &_R,
                 const Eigen::Vector3d &_T,
                 int _FixP,int _MovP,double _Err)
        {
            R=_R;
            T=_T;
            FixP=_FixP;
            MovP=_MovP;
            Err=_Err;
        }

        inline bool operator <(const Trasform &_T1)const
        {
            assert(FixP>=0);
            assert(MovP>=0);
            return (Err<_T1.Err);
        }

        Trasform()
        {
            R.setIdentity();
            T=Eigen::Vector3d(0,0,0);
            FixP=-1;
            MovP=-1;
            Err=-1;
        }
    };

    //the indexed troasform
    std::vector<std::vector<Trasform> > TransMatrix;
    std::vector<std::vector<std::vector<double > > > PointConfig;

    //the sorted ones
    std::vector<std::vector<Trasform> > SortedTrasnf;

public:

    double ComputeError(const std::vector<std::vector<double > > &PFix,
                        const std::vector<std::vector<double > > &PMov,
                        const Eigen::Matrix3d &R,const Eigen::Vector3d &T)
    {
        std::vector<std::vector<double > > PTest=PMov;
        assert(PFix.size()==PMov.size());
        PointMatch::ApplyTrasformRigidMatch(PTest,R,T);
        double Err=0;
        for (size_t i=0;i<PTest.size();i++)
            Err+=Distance(PTest[i],PFix[i]);

        return Err;
    }

    //for each point cloud, for each vertex X,Y,Z
    void InitMatches(const std::vector<std::vector<std::vector<double > > > &_PointConfig)
    {
        PointConfig=_PointConfig;
        int numConf=PointConfig.size();

        //allocate matrix (numConf X numConf)
        TransMatrix.clear();
        TransMatrix.resize(numConf,std::vector<Trasform>(numConf));

        //compute rigid match
        for (size_t i=0;i<PointConfig.size();i++)
            for (size_t j=0;j<PointConfig.size();j++)
            {
                if (i==j)
                {
                    TransMatrix[i][j].FixP=i;
                    TransMatrix[i][j].MovP=j;
                    TransMatrix[i][j].Err=0;
                }
                else
                {
                    //same number of vertices
                    assert(PointConfig[i].size()==PointConfig[j].size());
                    Eigen::Matrix3d R;
                    Eigen::Vector3d T;
                    PointMatch::ComputeLeastSquaresRigidMotion(PointConfig[i],PointConfig[j],R,T);
                    TransMatrix[i][j].FixP=i;
                    TransMatrix[i][j].MovP=j;
                    TransMatrix[i][j].R=R;
                    TransMatrix[i][j].T=T;
                    TransMatrix[i][j].Err=ComputeError(PointConfig[i],PointConfig[j],R,T);

                }
            }

        //then sort them considering the distance
        SortedTrasnf.clear();
        for (size_t i=0;i<TransMatrix.size();i++)
        {
            //copy the entire row
            std::vector<Trasform> CurrTrans=TransMatrix[i];

            //one transform with respect to others
            assert(CurrTrans.size()==PointConfig.size());

            //then sort
            std::sort(CurrTrans.begin(),CurrTrans.end());

            //check consistency
            assert(CurrTrans[0].T==Eigen::Vector3d(0,0,0));
            assert(CurrTrans[0].R==Eigen::Matrix3d::Identity());
            assert(CurrTrans[0].Err==0);
            assert(CurrTrans[0].FixP==(int)i);
            assert(CurrTrans[0].MovP==(int)i);

            //then copy
            SortedTrasnf.push_back(CurrTrans);
        }
    }

    //return the index-sorted from the reference Ref index
    void GetSurtedSequencePoint(const size_t RefIndex,
                                const size_t CurrIndex,
                                size_t &CurrLabel,double &currError,
                                std::vector<std::vector<double > > &TransfPoint)
    {
        assert(RefIndex<SortedTrasnf.size());
        assert(CurrIndex<SortedTrasnf[RefIndex].size());

        Trasform currTrans=SortedTrasnf[RefIndex][CurrIndex];
        assert(currTrans.FixP==(int)RefIndex);

        CurrLabel=currTrans.MovP;
        currError=currTrans.Err;

        //get the point cloud
        TransfPoint=PointConfig[currTrans.MovP];

        //then transform
        PointMatch::ApplyTrasformRigidMatch(TransfPoint,currTrans.R,currTrans.T);
    }

};

#endif
