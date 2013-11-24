#ifndef PANIMAGEFILTER_H
#define PANIMAGEFILTER_H

#include "panimage.h"
#include "panimagehistproc.h"

#define FRONT_SIDE 0
#define REVERSE_SIDE 1

#define LEFT_BORDER 0
#define RIGHT_BORDER 1

#define CIRCLE_WIDTH 3

#define SEARCH_STEP 1

#define BIG_CIRCLE_MIN 93
#define BIG_CIRCLE_MAX 98

#define SMALL_CIRCLE_MIN 2
#define SMALL_CIRCLE_MAX 7

#define WIDTH 752
#define HEIGHT 480
#define R2DIVNUM 200
#define WITHIN_CIRCLE 1
#define NON_WITHIN_CIRCLE 0
static unsigned int H[WIDTH][HEIGHT][R2DIVNUM];
static unsigned int r2ValArray[R2DIVNUM];

typedef struct
{
	unsigned int a;
	unsigned int b;
	unsigned int r;
	unsigned long r2;
	unsigned long r2Div;
	bool hasValue;
}_Pan_Circle;

// init the r-�� space
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


// init the r-�� space
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


class PanImageFilter
{
	static PanImageFilter* instance;

public:
	PanImageFilter();
	~PanImageFilter();

	static PanImageFilter* GetInstance();
	static void Destroy();

	unsigned int CalcCombosX2Y2R2(unsigned int r2);

	void SobelSharpen(PanImage& image);
	void MedianFilter(PanImage& image);
	void Erode(PanImage& image);
	void Dilate(PanImage& image);
	void OtsuBinary(PanImage& image);
	_Pan_Circle PanImageFilter::HoughTransform(PanImage &image,
										unsigned int rMin, 
										unsigned int rMax,
										unsigned int step,
										unsigned int iMin,
										unsigned int iMax,
										unsigned int jMin,
										unsigned int jMax,
										unsigned int div);
	_Pan_Circle PanImageFilter::HoughTransform(PanImage &image,
										unsigned int rMin, 
										unsigned int rMax,
										unsigned int step,
										unsigned int iMin,
										unsigned int iMax,
										unsigned int jMin,
										unsigned int jMax,
										unsigned int div,
										_Pan_Circle bigCircle); 
	void TotalProcessing(PanImage& image);
	void LabelString(PanImage& image, _Pan_Circle bigCircle, _Pan_Circle smallCircle);
	void HoleFill(PanImage& image);
};

#endif // PANIMAGEFILTER_H
