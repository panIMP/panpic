#ifndef ALG_DETECT_H
#define ALG_DETECT_H


#include "baseImage.h"
#include "baseThread.h"
#include "baseTransform.h"

#include "algFilter.h"


namespace AlgDetect {
    static bool isInited = false;

    static const int CIRCLE_WIDTH = 3;
    static const int SEARCH_STEP = 4;
    static const int BIG_CIRCLE_MIN = 95;
    static const int BIG_CIRCLE_MAX = 97;
    static const int SMALL_CIRCLE_MIN = 2;
    static const int SMALL_CIRCLE_MAX = 8;

    static const int NON_WITHIN_CIRCLE = 0;
    static const int WITHIN_CIRCLE = 1;

    // init the r-¦È space
    static const int sinValue[360] =
    {
        0,    17,	34,   52,  70,  87,  104, 122, 139, 156, 174, 191, 208, 225, 242,
        259,  276,  292,  309, 326, 342, 358, 375, 391, 407, 423, 438, 454, 469, 485,
        500,  515,  530,  545, 559, 574, 588, 602, 616, 629, 643, 656, 669, 682, 695,
        707,  719,  731,  743, 755, 766, 777, 788, 799, 809, 819, 829, 839, 848, 857,
        866,  875,  883,  891, 899, 906, 914, 921, 927, 934, 940, 946, 951, 956, 961,
        966,  970,  974,  978, 982, 985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,

        1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 985, 982, 978, 974,  970,
        966,  961,  956, 951, 946, 940, 934, 927, 921, 914, 906, 899, 891, 883,  875,
        866,  857,  848, 839, 829, 819, 809, 799, 788, 777, 766, 755, 743, 731,  719,
        707,  695,  682, 669, 656, 643, 629, 616, 602, 588, 574, 559, 545, 530,  515,
        500,  485,  469, 454, 438, 423, 407, 391, 375, 358, 342, 326, 309, 292,  276,
        259,  242,  225, 208, 191, 174, 156, 139, 122, 104, 87,  70,  52,  34,   17,

        0,    17,	34,   52,  70,  87,  104, 122, 139, 156, 174, 191, 208, 225, 242,
        259,  276,  292,  309, 326, 342, 358, 375, 391, 407, 423, 438, 454, 469, 485,
        500,  515,  530,  545, 559, 574, 588, 602, 616, 629, 643, 656, 669, 682, 695,
        707,  719,  731,  743, 755, 766, 777, 788, 799, 809, 819, 829, 839, 848, 857,
        866,  875,  883,  891, 899, 906, 914, 921, 927, 934, 940, 946, 951, 956, 961,
        966,  970,  974,  978, 982, 985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,

        1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 985, 982, 978, 974,  970,
        966,  961,  956, 951, 946, 940, 934, 927, 921, 914, 906, 899, 891, 883,  875,
        866,  857,  848, 839, 829, 819, 809, 799, 788, 777, 766, 755, 743, 731,  719,
        707,  695,  682, 669, 656, 643, 629, 616, 602, 588, 574, 559, 545, 530,  515,
        500,  485,  469, 454, 438, 423, 407, 391, 375, 358, 342, 326, 309, 292,  276,
        259,  242,  225, 208, 191, 174, 156, 139, 122, 104, 87,  70,  52,  34,   17,
    };

    // init the r-¦È space
    static const int cosValue[360] =
    {
        1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 985, 982, 978, 974,  970,
        966,  961,  956, 951, 946, 940, 934, 927, 921, 914, 906, 899, 891, 883,  875,
        866,  857,  848, 839, 829, 819, 809, 799, 788, 777, 766, 755, 743, 731,  719,
        707,  695,  682, 669, 656, 643, 629, 616, 602, 588, 574, 559, 545, 530,  515,
        500,  485,  469, 454, 438, 423, 407, 391, 375, 358, 342, 326, 309, 292,  276,
        259,  242,  225, 208, 191, 174, 156, 139, 122, 104, 87,  70,  52,  34,   17,

        0,    17,	34,   52,  70,  87,  104, 122, 139, 156, 174, 191, 208, 225, 242,
        259,  276,  292,  309, 326, 342, 358, 375, 391, 407, 423, 438, 454, 469, 485,
        500,  515,  530,  545, 559, 574, 588, 602, 616, 629, 643, 656, 669, 682, 695,
        707,  719,  731,  743, 755, 766, 777, 788, 799, 809, 819, 829, 839, 848, 857,
        866,  875,  883,  891, 899, 906, 914, 921, 927, 934, 940, 946, 951, 956, 961,
        966,  970,  974,  978, 982, 985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,

        1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 985, 982, 978, 974,  970,
        966,  961,  956, 951, 946, 940, 934, 927, 921, 914, 906, 899, 891, 883,  875,
        866,  857,  848, 839, 829, 819, 809, 799, 788, 777, 766, 755, 743, 731,  719,
        707,  695,  682, 669, 656, 643, 629, 616, 602, 588, 574, 559, 545, 530,  515,
        500,  485,  469, 454, 438, 423, 407, 391, 375, 358, 342, 326, 309, 292,  276,
        259,  242,  225, 208, 191, 174, 156, 139, 122, 104, 87,  70,  52,  34,   17,

        0,    17,	34,   52,  70,  87,  104, 122, 139, 156, 174, 191, 208, 225, 242,
        259,  276,  292,  309, 326, 342, 358, 375, 391, 407, 423, 438, 454, 469, 485,
        500,  515,  530,  545, 559, 574, 588, 602, 616, 629, 643, 656, 669, 682, 695,
        707,  719,  731,  743, 755, 766, 777, 788, 799, 809, 819, 829, 839, 848, 857,
        866,  875,  883,  891, 899, 906, 914, 921, 927, 934, 940, 946, 951, 956, 961,
        966,  970,  974,  978, 982, 985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,
    };

    static int*** H = 0;
    static int _r2DivNum = 0;

    typedef struct
    {
        int a;
        int b;
        int r;
        long r2;
        long r2Div;
        bool hasValue;
    }_Pan_Circle;

    void InitGlobalVaribles(baseImage&);

    class Hough;
    class Hough2;
    class CicleIncisionDetection;
    class LabelString;
}


class AlgDetect::Hough : public baseTransform
{
public:
    Hough(  baseImage &image,
            int rMin,
            int rMax,
            int step,
            int iMin,
            int iMax,
            int jMin,
            int jMax,
            int div,
            _Pan_Circle& circle);

	void apply();

private:
	baseImage& image;

	_Pan_Circle& circle;
	int rMin; 
	int rMax;
	int step;
	int iMin;
	int iMax;
	int jMin;
	int jMax;
	int div;
};


class AlgDetect::Hough2 : public baseTransform
{
public:
    Hough2( baseImage &image,
            int rMin,
            int rMax,
            int step,
            int iMin,
            int iMax,
            int jMin,
            int jMax,
            int div,
            _Pan_Circle& bigCircle,
            _Pan_Circle& smallCircle);

	void apply();

private:
	baseImage& image;

	_Pan_Circle& bigCircle;
	_Pan_Circle& smallCircle;
	int rMin; 
	int rMax;
	int step;
	int iMin;
	int iMax;
	int jMin;
	int jMax;
	int div;
};


class AlgDetect::LabelString : public baseTransform
{
public:
    LabelString(baseImage& image, _Pan_Circle& bigCircle, _Pan_Circle& smallCircle);

	void apply();

private:
	baseImage& image;

	_Pan_Circle& bigCircle;
	_Pan_Circle& smallCircle;
};


class AlgDetect::CicleIncisionDetection : public baseTransform
{
public:
    CicleIncisionDetection( baseImage &image,
                            int rMin,
                            int rMax,
                            int step,
                            int iMin,
                            int iMax,
                            int jMin,
                            int jMax,
                            int div,
                            _Pan_Circle& bigCircle,
                            _Pan_Circle& smallCircle);

	void apply();

private:
	baseImage& image;

	_Pan_Circle& bigCircle;
	_Pan_Circle& smallCircle;
	int rMin; 
	int rMax;
	int step;
	int iMin;
	int iMax;
	int jMin;
	int jMax;
	int div;
};


#endif
