//#include <cmath>

#include <vector>
#include <iostream>
#include <iomanip>
#include "point_match.h"
#include "multiple_match.h"




double GenerateRand(const double minV,const double maxV)
{
    assert(maxV>minV);
    int Interval=100000;
    double alpha=((double)(rand()%Interval))/(double)Interval;
    double Val=minV+(alpha*(maxV-minV));
    return Val;
}

void RandomlyPerturb(std::vector<std::vector<double> > &Pos,
                     const double &interval)
{
    for (size_t i=0;i<Pos.size();i++)
    {
        assert(Pos[i].size()==3);
        for (size_t j=0;j<3;j++)
        {
            double perturb=GenerateRand(-interval,interval);
            Pos[i][j]+=perturb;
        }
    }
}

void GeneratePointCloud(const int Num,const double interval,
                        std::vector<std::vector<double> > &Pos)
{
    Pos.clear();
    //initialize as zero
    Pos.resize(Num,std::vector<double>(3,0));
    RandomlyPerturb(Pos,interval);
}

std::vector<std::vector<std::vector<double> > > PClouds;

size_t NumPoints=30;
size_t NumTest=5;

void GeneratePointClouds(const double interval)
{
    PClouds.clear();
    std::vector<std::vector<double> > Pos0;
    GeneratePointCloud(NumPoints,interval,Pos0);

    //copy the same points
    PClouds.resize(NumTest,Pos0);

    //then perturbs
    double curr_delta=interval/50;
    for (size_t i=1;i<PClouds.size();i++)
        RandomlyPerturb(PClouds[i],curr_delta*i);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    std::cout<<"** GENERATING POINTS **"<<std::endl;
    GeneratePointClouds(5);

    std::cout<<"** INIT MATCHES **"<<std::endl;
    MultipleMatch MMatch;
    MMatch.InitMatches(PClouds);

    std::cout<<"** QUERY TEST **"<<std::endl;
    for (size_t i=0;i<NumTest;i++)
    {
        std::cout<<std::endl;
        std::cout<<"** Quertying "<<i<<std::endl;
        for (size_t j=0;j<NumTest;j++)
        {
            size_t curr_label;
            double curr_error;
            std::vector<std::vector<double > > TransfPoint;
            MMatch.GetSurtedSequencePoint(i,j,curr_label,curr_error,TransfPoint);
            std::cout<<"Label: "<<curr_label<<" error: "<<curr_error<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<std::endl;
    }
    std::cout<<"** DONE **"<<std::endl;
}


//int main(int argc, char *argv[])
//{
//    (void)argc;
//    (void)argv;
//    std::vector<std::vector<double> > PFix,PMov;
//    //crate 8 points of a cube

//    //INITIALIZE 8 POINTS OF A CUBE

//    // point 0,0,0
//    std::vector<double> P0;
//    P0.push_back(0);//X of a point
//    P0.push_back(0);//Y of a point
//    P0.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P0);

//    // point 0,1,0
//    std::vector<double> P1;
//    P1.push_back(0);//X of a point
//    P1.push_back(1);//Y of a point
//    P1.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P1);

//    // point 1,0,0
//    std::vector<double> P2;
//    P2.push_back(1);//X of a point
//    P2.push_back(0);//Y of a point
//    P2.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P2);

//    // point 1,1,0
//    std::vector<double> P3;
//    P3.push_back(1);//X of a point
//    P3.push_back(1);//Y of a point
//    P3.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P3);

//    // point 0,0,1
//    std::vector<double> P4;
//    P4.push_back(0);//X of a point
//    P4.push_back(0);//Y of a point
//    P4.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P4);

//    // point 0,1,1
//    std::vector<double> P5;
//    P5.push_back(0);//X of a point
//    P5.push_back(1);//Y of a point
//    P5.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P5);

//    // point 1,0,1
//    std::vector<double> P6;
//    P6.push_back(1);//X of a point
//    P6.push_back(0);//Y of a point
//    P6.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P6);

//    // point 1,1,1
//    std::vector<double> P7;
//    P7.push_back(1);//X of a point
//    P7.push_back(1);//Y of a point
//    P7.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P7);

//    //THEN COPY THE CUBE
//    PMov=PFix;

//    //translate along the X of 0.3 all the points
//    PMov[0][0]+=0.3;
//    PMov[1][0]+=0.3;
//    PMov[2][0]+=0.3;
//    PMov[3][0]+=0.3;
//    PMov[4][0]+=0.3;
//    PMov[5][0]+=0.3;
//    PMov[6][0]+=0.3;
//    PMov[7][0]+=0.3;

//    std::cout << std::fixed;
//    std::cout << std::setprecision(2);

//    //PRINT THE POSITIONS BEFORE THE CALCULATION
//    std::cout<<"POSITIONS BEFORE POINT MATCH"<<std::endl;
//    for (size_t i=0;i<PMov.size();i++)
//        std::cout<<"X:"<<PMov[i][0]<<" Y:"<<PMov[i][1]<<" Z:"<<PMov[i][2]<<","<<std::endl;

//     //then modify the PMov to match pFix in least square sense
//    PointMatch::TrasformRigidMatch(PFix,PMov);

//    std::cout<<"POSITIONS AFTER POINT MATCH"<<std::endl;
//    for (size_t i=0;i<PMov.size();i++)
//        std::cout<<"X:"<<PMov[i][0]<<" Y:"<<PMov[i][1]<<" Z:"<<PMov[i][2]<<","<<std::endl;

//}

//int main(int argc, char *argv[])
//{
//    std::vector<std::vector<double> > PFix,PMov;
//    //crate 8 points of a cube

//    //INITIALIZE 8 POINTS OF A CUBE

//    // point 0,0,0
//    std::vector<double> P0;
//    P0.push_back(0);//X of a point
//    P0.push_back(0);//Y of a point
//    P0.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P0);

//    // point 0,1,0
//    std::vector<double> P1;
//    P1.push_back(0);//X of a point
//    P1.push_back(1);//Y of a point
//    P1.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P1);

//    // point 1,0,0
//    std::vector<double> P2;
//    P2.push_back(1);//X of a point
//    P2.push_back(0);//Y of a point
//    P2.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P2);

//    // point 1,1,0
//    std::vector<double> P3;
//    P3.push_back(1);//X of a point
//    P3.push_back(1);//Y of a point
//    P3.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P3);

//    // point 0,0,1
//    std::vector<double> P4;
//    P4.push_back(0);//X of a point
//    P4.push_back(0);//Y of a point
//    P4.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P4);

//    // point 0,1,1
//    std::vector<double> P5;
//    P5.push_back(0);//X of a point
//    P5.push_back(1);//Y of a point
//    P5.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P5);

//    // point 1,0,1
//    std::vector<double> P6;
//    P6.push_back(1);//X of a point
//    P6.push_back(0);//Y of a point
//    P6.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P6);

//    // point 1,1,1
//    std::vector<double> P7;
//    P7.push_back(1);//X of a point
//    P7.push_back(1);//Y of a point
//    P7.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P7);

//    //THEN COPY THE CUBE
//    PMov=PFix;

//    //translate along the X of 0.3 all the points
//    PMov[0][0]+=0.3;
//    PMov[1][0]+=0.3;
//    PMov[2][0]+=0.3;
//    PMov[3][0]+=0.3;
//    PMov[4][0]+=0.3;
//    PMov[5][0]+=0.3;
//    PMov[6][0]+=0.3;
//    PMov[7][0]+=0.3;

//    std::cout << std::fixed;
//    std::cout << std::setprecision(2);

//    //PRINT THE POSITIONS BEFORE THE CALCULATION
//    std::cout<<"POSITIONS BEFORE POINT MATCH"<<std::endl;
//    for (size_t i=0;i<PMov.size();i++)
//        std::cout<<"X:"<<PMov[i][0]<<" Y:"<<PMov[i][1]<<" Z:"<<PMov[i][2]<<","<<std::endl;

//     //then modify the PMov to match pFix in least square sense
//    PointMatch::TrasformRigidMatch(PFix,PMov);

//    std::cout<<"POSITIONS AFTER POINT MATCH"<<std::endl;
//    for (size_t i=0;i<PMov.size();i++)
//        std::cout<<"X:"<<PMov[i][0]<<" Y:"<<PMov[i][1]<<" Z:"<<PMov[i][2]<<","<<std::endl;
//}

//int main(int argc, char *argv[])
//{
//    (void)argc;
//    (void)argv;
//    std::vector<std::vector<double> > PFix,PMov;
//    //crate 8 points of a cube

//    //INITIALIZE 8 POINTS OF A CUBE

//    // point 0,0,0
//    std::vector<double> P0;
//    P0.push_back(0);//X of a point
//    P0.push_back(0);//Y of a point
//    P0.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P0);

//    // point 0,1,0
//    std::vector<double> P1;
//    P1.push_back(0);//X of a point
//    P1.push_back(1);//Y of a point
//    P1.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P1);

//    // point 1,0,0
//    std::vector<double> P2;
//    P2.push_back(1);//X of a point
//    P2.push_back(0);//Y of a point
//    P2.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P2);

//    // point 1,1,0
//    std::vector<double> P3;
//    P3.push_back(1);//X of a point
//    P3.push_back(1);//Y of a point
//    P3.push_back(0);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P3);

//    // point 0,0,1
//    std::vector<double> P4;
//    P4.push_back(0);//X of a point
//    P4.push_back(0);//Y of a point
//    P4.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P4);

//    // point 0,1,1
//    std::vector<double> P5;
//    P5.push_back(0);//X of a point
//    P5.push_back(1);//Y of a point
//    P5.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P5);

//    // point 1,0,1
//    std::vector<double> P6;
//    P6.push_back(1);//X of a point
//    P6.push_back(0);//Y of a point
//    P6.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P6);

//    // point 1,1,1
//    std::vector<double> P7;
//    P7.push_back(1);//X of a point
//    P7.push_back(1);//Y of a point
//    P7.push_back(1);//Z of a point
//    //add the point to the set of all points
//    PFix.push_back(P7);

//    //THEN COPY THE CUBE
//    PMov=PFix;

//    //translate along the X of 0.3 all the points
//    PMov[0][0]+=0.3;
//    PMov[1][0]+=0.3;
//    PMov[2][0]+=0.3;
//    PMov[3][0]+=0.3;
//    PMov[4][0]+=0.3;
//    PMov[5][0]+=0.3;
//    PMov[6][0]+=0.3;
//    PMov[7][0]+=0.3;

//    std::cout << std::fixed;
//    std::cout << std::setprecision(2);

//    //PRINT THE POSITIONS BEFORE THE CALCULATION
//    std::cout<<"POSITIONS BEFORE POINT MATCH"<<std::endl;
//    for (size_t i=0;i<PMov.size();i++)
//        std::cout<<"X:"<<PMov[i][0]<<" Y:"<<PMov[i][1]<<" Z:"<<PMov[i][2]<<","<<std::endl;

//     //then modify the PMov to match pFix in least square sense
//    PointMatch::TrasformRigidMatch(PFix,PMov);

//    std::cout<<"POSITIONS AFTER POINT MATCH"<<std::endl;
//    for (size_t i=0;i<PMov.size();i++)
//        std::cout<<"X:"<<PMov[i][0]<<" Y:"<<PMov[i][1]<<" Z:"<<PMov[i][2]<<","<<std::endl;

//}
