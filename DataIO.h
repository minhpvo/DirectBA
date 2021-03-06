#if !defined(ULTILITY_H )
#define ULTILITY_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <omp.h>
#include <stdarg.h>

#include <ceres/ceres.h>
#include <ceres/rotation.h>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <Eigen/Dense>

#include "DataStructure.h"
#include "MathUlti.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace cv;
using namespace std;

void makeDir(char *Fname);
int IsFileExist(char *Fname, bool silient = true);

int ReadCorpusInfo(char *Fname, Corpus &data, double scale = 1.0);
int ReadCalibInfo(char *BAfileName, Corpus &CorpusData, double scale = 1.0);
int ReadVideoDataI(char *Path, VideoData &vInfo, int viewID, int startTime, int stopTime, double scale = 1.0, double threshold = 3, int ninliersThresh = 40, int silent = 1);

void ReadSudiptaDepth(char *Path, ImgData &imdat, int i);
bool WriteInvDepthToImage(char *Fname, ImgData &imdat);
bool WriteInvDepthToImage(char *Fname, float *depth, int width, int height, double minDepth, double maxDepth);

int ReadSynthFile(char *Path, Corpus &CorpusData, int SynthID = 0);
int WriteSynthFile(char *Path, Corpus &CorpusData, int SynthID = 0);

template <class myType> bool WriteGridBinary(char *fn, myType *data, int width, int height, bool  verbose = false)
{
	ofstream fout;
	fout.open(fn, ios::binary);
	if (!fout.is_open())
	{
		if (verbose)
			cout << "Cannot write: " << fn << endl;
		return false;
	}

	for (int j = 0; j < height; ++j)
		for (int i = 0; i < width; ++i)
			fout.write(reinterpret_cast<char *>(&data[i + j*width]), sizeof(myType));
	fout.close();

	return true;
}
template <class myType> bool ReadGridBinary(char *fn, myType *data, int width, int height, bool  verbose = false)
{
	ifstream fin;
	fin.open(fn, ios::binary);
	if (!fin.is_open())
	{
		cout << "Cannot open: " << fn << endl;
		return false;
	}
	if (verbose)
		cout << "Load " << fn << endl;

	for (int j = 0; j < height; ++j)
		for (int i = 0; i < width; ++i)
			fin.read(reinterpret_cast<char *>(&data[i + j*width]), sizeof(myType));
	fin.close();

	return true;
}

bool WriteGridToImage(char *fname, bool *Img, int width, int height, int nchannels);
bool WriteGridToImage(char *fname, int *Img, int width, int height, int nchannels);
bool WriteGridToImage(char *fname, unsigned char *Img, int width, int height, int nchannels);
bool WriteGridToImage(char *fname, double *Img, int width, int height, int nchannels);

bool ReadFlowDataBinary(char *fnX, char *fnY, Point2f *fxy, int width, int height);

int  read_pfm_file(const std::string& filename, ImgData &depthmap);
cv::Mat read_pfm_file(const std::string& filename);
void save_pfm_file(const std::string& filename, const cv::Mat& image);

int ExtractVideoFrames(char *Path, char *inName, int startF, int stopF, int increF, int rotateImage, int nchannels, int Usejpg, double scale = 1.0);

#endif
