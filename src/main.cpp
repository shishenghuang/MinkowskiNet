

#include <iostream>
#include <vector>
#include <stdlib.h>

#include "SemanticsUtil.h"
#include "glog/logging.h"

using namespace std;

bool readOFF(char* filename , double* points_colors , int& pnum){
    FILE* fp = fopen(filename , "r");
    if(fp == NULL){
        LOG(INFO) << "Failed to read off file " << filename;
        return false;
    }
    int pn, fn , cc;
    char buf[255];
    fscanf(fp, "%s" , buf);
    fscanf(fp , "%d %d %d" , &pn , &fn , &cc);
    points_colors = new double[6*pn];
    double x,y,z,r,g,b;
    for(int i = 0  ; i < pn ; i ++){
        fscanf(fp, "%lf %lf %lf %lf %lf %lf", &x, &y, &z, &r, &g, &b);
        int index = 6 * i;
        points_colors[index+0]= x;
        points_colors[index+1]= y;
        points_colors[index+2]= z;
        points_colors[index+3]= r;
        points_colors[index+4]= g;
        points_colors[index+5]= b;
    }
    fclose(fp);
    pnum = pn;

    return true;
}

void WritePoints(const char* filename,
                 int n_supervoxels,
                 double* points,
                 int pnum,
                 int* labels) {

    vector<int> colors(pnum*3);
    vector<int> svcolors(n_supervoxels * 3);
    std::mt19937 random;
    for(int i = 0 ; i < n_supervoxels ; i ++){
        int r, g , b, alpha;
        colormap(random() , alpha , r, g, b);
        svcolors[3*i+0] = r;
        svcolors[3*i+1] = g;
        svcolors[3*i+2] = b;
    }
    for (int i = 0; i < pnum; ++i) {
        int l = labels[i];
        colors[3*i+0] = svcolors[3*l+0];
        colors[3*i+1] = svcolors[3*l+1];
        colors[3*i+2] = svcolors[3*l+2];                
    }

    FILE* fp = fopen(filename , "w+");
    for(int i = 0 ; i < pnum ; i ++){
        fprintf(fp, "%lf %lf %lf %d %d %d\n" , points[6*i+0] , 
                points[6*i+1] , points[6*i+2] , colors[3*i+0] , colors[3*i+1], colors[3*i+2]);
    }
    fclose(fp);

//    system(filename);
}


int main(){

    char* filename = "../testdata/test.off";
    double* points_colors;
    int* labels;
    int pnum;
    readOFF(filename , points_colors , pnum);

    SuperVoxel::SemanticsUtil sem;
    sem.predict(points_colors , pnum , labels);
    WritePoints("out.xyz" , 38 , points_colors , pnum , labels);

    return 0;
}
