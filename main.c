#include"highgui.h"
#include"stdio.h"
#include"cv.h"
#include"math.h"
#include"windows.h"
#include"outText.h"
//全局句柄
HWND hwnd;
//开关
char flag = 0;
//设置帽子全局变量
IplImage* hat1;
IplImage* hat2;
IplImage* hat3;
IplImage* hat4;
IplImage* hat5;
IplImage* hat6;
//定义全局结构体方便接收与使用人脸检测数据
struct faceImfro
{
	CvPoint point;
	int weight;
	int height;
}face;
//加载原图
IplImage* Input_Image_Init();
void Hat_Init();
void detect_and_draw(IplImage* img);
void Tohead(IplImage* img, IplImage* hat);
void TosaveImage(IplImage* img);
int main()
{
	//处理图像
	IplImage* src;
	//初始显示第一个帽子
	int hat_count = 1;
	//更换帽子
	char count = 0;
	//帽子的最大数量
	char hat_max = 6;
	//初始化界面窗口
	outText();
	//加载帽子
	Hat_Init();
	//加载图像初始化模块
	src = Input_Image_Init();
	//cvNamedWindow("原图", CV_WINDOW_NORMAL);
	cvNamedWindow("效果图", CV_WINDOW_NORMAL);
	//cvShowImage("原图", src);
	//人脸检测
	detect_and_draw(src);
	while (1)
	{
		if (flag)
		{
			//选择帽子
			switch (hat_count)
			{
			case(1):Tohead(src, hat1); flag = 0; break;
			case(2):Tohead(src, hat2); flag = 0; break;
			case(3):Tohead(src, hat3); flag = 0; break;
			case(4):Tohead(src, hat4); flag = 0; break;
			case(5):Tohead(src, hat5); flag = 0; break;
			case(6):Tohead(src, hat6); flag = 0; break;
				//...
			default:printf("尽请期待"); flag = 0; break;
			}
			//获取桌面句柄
			hwnd = GetDesktopWindow();
			//接受用户选择返回值
			//提醒用户是否保存图像
			int result = MessageBox(hwnd, TEXT("是否要保存图像"), TEXT("保存提示框"), MB_ICONINFORMATION | MB_YESNO);
			switch (result)
			{
				//选择yes，保存图像
			case(IDYES):
				outText(); 
				MessageBox(hwnd, TEXT("请返回控制台执行相关操作"), TEXT("保存操作提示框"), MB_OK);
				TosaveImage(src);
				break;
				//选择no，不保存图像
			case(IDNO):
				outText();
				MessageBox(hwnd, TEXT("不保存图像"), TEXT("保存操作提示框"), MB_OK); 
			    break;
			}
		}
		count = cvWaitKey(30);
		switch (count)
		{
			//按下q更换图像
		case(81):case(113):
					MessageBox(hwnd, TEXT("请返回控制台执行相关操作"), TEXT("更换图片操作提示框"), MB_OK);
					outText(); 
					src = Input_Image_Init();
					detect_and_draw(src);
			//按下空格更换帽子
		case(32):hat_count++; flag=1; break;
			//按下ESC退出程序
		case(27): return 0; break;
		}
		if (hat_count > hat_max+1)
		{
			//清置
			hat_count = 1;
		}

	}
	//清除图像存储内存
	cvReleaseImage(&src);
	cvReleaseImage(&hat1);
	cvReleaseImage(&hat2);
	cvReleaseImage(&hat3);
	cvReleaseImage(&hat4);
	cvReleaseImage(&hat5);
	//cvDestroyWindow("原图");
	cvDestroyWindow("效果图");
	return 0;
}
//输出图像初始化
IplImage* Input_Image_Init()
{
	flag = 1;
	//开辟动态内存接受用户输入图像路径
	char* s = (char*)malloc(sizeof(char) * 100);
	printf("请输入要处理图像的地址:\n");
	gets(s);

	outText();

	printf("你输入的处理图像地址为:\n");
	puts(s);
	//按照用户输入加载图像
	IplImage* img = cvLoadImage(s, 1);
	if (!img)
	{
		printf("error1!读取img失败~\n");
		printf("请检查图片输入路径是否正确！\n");
		exit(0);
	}
	//释放动态内存
	free(s);
	return img;
}
//帽子图像加载初始化
void Hat_Init()
{
	 hat1 = cvLoadImage("D:\\大学\\计算机作业\\FindAndHead\\Image_Hat\\hat.png", 1);
	 hat2 = cvLoadImage("D:\\大学\\计算机作业\\FindAndHead\\Image_Hat\\hat1.jpg", 1);
	 hat3 = cvLoadImage("D:\\大学\\计算机作业\\FindAndHead\\Image_Hat\\hat2.jpg", 1);
	 hat4 = cvLoadImage("D:\\大学\\计算机作业\\FindAndHead\\Image_Hat\\hat3.jpg", 1);
	 hat5 = cvLoadImage("D:\\大学\\计算机作业\\FindAndHead\\Image_Hat\\hat4.jpg", 1);
	 hat6 = cvLoadImage("D:\\大学\\计算机作业\\FindAndHead\\Image_Hat\\hat5.png", 1);
	 if (!hat1)
	 {
		 printf("error2!读取hat1失败~");
		 printf("请检查帽子1输入路径是否正确！\n");
		 exit(0);
	 }
	 if (!hat2)
	 {
		 printf("error3!读取hat2失败~");
		 printf("请检查帽子2输入路径是否正确！\n");
		 exit(0);
	 }
	 if (!hat3)
	 {
		 printf("error4!读取hat3失败~");
		 printf("请检查帽子3输入路径是否正确！\n");
		 exit(0);
	 }
	 if (!hat4)
	 {
		 printf("error5!读取hat4失败~");
		 printf("请检查帽子4输入路径是否正确！\n");
		 exit(0);
	 }
	 if (!hat5)
	 {
		 printf("error6!读取hat5失败~");
		 printf("请检查帽子5输入路径是否正确！\n");
		 exit(0);
	 }
	 if (!hat6)
	 {
		 printf("error7!读取hat6失败~");
		 printf("请检查帽子6输入路径是否正确！\n");
		 exit(0);
	 }
}
void detect_and_draw(IplImage* img)
{
	//调整系数
	double scale = 1.3;
	//定义画框颜色
	static CvScalar colors[] = { { 0,0,255 } };
	//加载人脸分类器
	char* cascade_name = "D:\\gongju\\opencv3.1.0\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt2.xml";
	//char* cascade_name = "D:\\gongju\\opencv3.1.0\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0);
	//开辟工作内存
	CvMemStorage* storage = cvCreateMemStorage(0);
	//设置灰度图，检测在灰度图上检测
	IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);
	//调整图像大小，from分类器
	IplImage* small_img = cvCreateImage(cvSize(round(img->width / scale), round(img->height / scale)), 8, 1);
	cvCvtColor(img, gray, CV_BGR2GRAY);
	cvResize(gray, small_img, CV_INTER_LINEAR);
	//直方图均一化（取消噪点）
	cvEqualizeHist(small_img, small_img);
	//清除工作区内存
	cvClearMemStorage(storage);
	//人脸检测，并将其储存在CvSeq序列中
	CvSeq* objects = cvHaarDetectObjects(
		small_img,
		cascade,
		storage,
		1.1,//扫描步长
		3,//设置成功最小迭代次数
		CV_HAAR_FIND_BIGGEST_OBJECT,
		cvSize(30, 30),//人脸最小大小
					   //cvSize(small_img->width, small_img->height)
		cvSize(500, 500));//人脸最大大小，bad
						  //for (int i = 0; i < (objects ? objects->total : 0); i++)
						  //{
	CvPoint point;
	CvRect* r = (CvRect*)cvGetSeqElem(objects, 1);
	point.x = r->x + r->width;
	point.y = r->y + 0.5* r->height;
	face.point = point;
	face.weight = r->width;
	face.height = r->height;
	/*
	cvRectangle(
		img,
		cvPoint(r->x + r->width, r->y + 0.5* r->height),
		cvPoint(r->x + r->width + r->width, r->y + r->height + 0.5* r->height),
		//cvPoint(r->x + r->width + r->width, r->y + r->height + r->height),
		colors[0],
		1,
		1,
		0);
	//}*/
	//释放中间图像内存
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);

}
void Tohead(IplImage* img, IplImage* hat)
{
	IplImage* dst;
	//定义ROI
	cvSetImageROI(img,
				  cvRect(face.point.x, face.point.y - face.height,
				  face.weight, face.height));
	//dst= cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	//调整帽子大小
	dst = cvCreateImage(cvSize(face.weight, face.height), IPL_DEPTH_8U, 3);
	cvResize(hat, dst, CV_INTER_NN);
	//线性混合
	cvAddWeighted(img, 0, dst, 1, 0, img);
	//释放ROI内存
	cvResetImageROI(img);
	//显示效果图
	cvShowImage("效果图", img);
}
//存储图像
void TosaveImage(IplImage* img)
{
	outText();
	//开辟动态内存接受用户输入存储路径
	char* ss = (char*)malloc(sizeof(char) * 100);
	printf("请输入图像保存的地址:\n");
	gets(ss);
	//选择储存格式
	int p[2];
	p[0] = CV_IMWRITE_JPEG_QUALITY;
	p[1] = 90;
	//存储图像
	cvSaveImage(ss, img, p);
	outText();
	//存储图像成功提示框
	MessageBox(hwnd, TEXT("图像保存完成"), TEXT("保存操作提示框"), MB_OK);
	printf("图像保存地址为:\n");
	puts(ss);
	//释放动态内存
	free(ss);
}