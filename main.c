#include"highgui.h"
#include"stdio.h"
#include"cv.h"
#include"math.h"
#include"windows.h"
#include"outText.h"
//ȫ�־��
HWND hwnd;
//����
char flag = 0;
//����ñ��ȫ�ֱ���
IplImage* hat1;
IplImage* hat2;
IplImage* hat3;
IplImage* hat4;
IplImage* hat5;
IplImage* hat6;
//����ȫ�ֽṹ�巽�������ʹ�������������
struct faceImfro
{
	CvPoint point;
	int weight;
	int height;
}face;
//����ԭͼ
IplImage* Input_Image_Init();
void Hat_Init();
void detect_and_draw(IplImage* img);
void Tohead(IplImage* img, IplImage* hat);
void TosaveImage(IplImage* img);
int main()
{
	//����ͼ��
	IplImage* src;
	//��ʼ��ʾ��һ��ñ��
	int hat_count = 1;
	//����ñ��
	char count = 0;
	//ñ�ӵ��������
	char hat_max = 6;
	//��ʼ�����洰��
	outText();
	//����ñ��
	Hat_Init();
	//����ͼ���ʼ��ģ��
	src = Input_Image_Init();
	//cvNamedWindow("ԭͼ", CV_WINDOW_NORMAL);
	cvNamedWindow("Ч��ͼ", CV_WINDOW_NORMAL);
	//cvShowImage("ԭͼ", src);
	//�������
	detect_and_draw(src);
	while (1)
	{
		if (flag)
		{
			//ѡ��ñ��
			switch (hat_count)
			{
			case(1):Tohead(src, hat1); flag = 0; break;
			case(2):Tohead(src, hat2); flag = 0; break;
			case(3):Tohead(src, hat3); flag = 0; break;
			case(4):Tohead(src, hat4); flag = 0; break;
			case(5):Tohead(src, hat5); flag = 0; break;
			case(6):Tohead(src, hat6); flag = 0; break;
				//...
			default:printf("�����ڴ�"); flag = 0; break;
			}
			//��ȡ������
			hwnd = GetDesktopWindow();
			//�����û�ѡ�񷵻�ֵ
			//�����û��Ƿ񱣴�ͼ��
			int result = MessageBox(hwnd, TEXT("�Ƿ�Ҫ����ͼ��"), TEXT("������ʾ��"), MB_ICONINFORMATION | MB_YESNO);
			switch (result)
			{
				//ѡ��yes������ͼ��
			case(IDYES):
				outText(); 
				MessageBox(hwnd, TEXT("�뷵�ؿ���ִ̨����ز���"), TEXT("���������ʾ��"), MB_OK);
				TosaveImage(src);
				break;
				//ѡ��no��������ͼ��
			case(IDNO):
				outText();
				MessageBox(hwnd, TEXT("������ͼ��"), TEXT("���������ʾ��"), MB_OK); 
			    break;
			}
		}
		count = cvWaitKey(30);
		switch (count)
		{
			//����q����ͼ��
		case(81):case(113):
					MessageBox(hwnd, TEXT("�뷵�ؿ���ִ̨����ز���"), TEXT("����ͼƬ������ʾ��"), MB_OK);
					outText(); 
					src = Input_Image_Init();
					detect_and_draw(src);
			//���¿ո����ñ��
		case(32):hat_count++; flag=1; break;
			//����ESC�˳�����
		case(27): return 0; break;
		}
		if (hat_count > hat_max+1)
		{
			//����
			hat_count = 1;
		}

	}
	//���ͼ��洢�ڴ�
	cvReleaseImage(&src);
	cvReleaseImage(&hat1);
	cvReleaseImage(&hat2);
	cvReleaseImage(&hat3);
	cvReleaseImage(&hat4);
	cvReleaseImage(&hat5);
	//cvDestroyWindow("ԭͼ");
	cvDestroyWindow("Ч��ͼ");
	return 0;
}
//���ͼ���ʼ��
IplImage* Input_Image_Init()
{
	flag = 1;
	//���ٶ�̬�ڴ�����û�����ͼ��·��
	char* s = (char*)malloc(sizeof(char) * 100);
	printf("������Ҫ����ͼ��ĵ�ַ:\n");
	gets(s);

	outText();

	printf("������Ĵ���ͼ���ַΪ:\n");
	puts(s);
	//�����û��������ͼ��
	IplImage* img = cvLoadImage(s, 1);
	if (!img)
	{
		printf("error1!��ȡimgʧ��~\n");
		printf("����ͼƬ����·���Ƿ���ȷ��\n");
		exit(0);
	}
	//�ͷŶ�̬�ڴ�
	free(s);
	return img;
}
//ñ��ͼ����س�ʼ��
void Hat_Init()
{
	 hat1 = cvLoadImage("D:\\��ѧ\\�������ҵ\\FindAndHead\\Image_Hat\\hat.png", 1);
	 hat2 = cvLoadImage("D:\\��ѧ\\�������ҵ\\FindAndHead\\Image_Hat\\hat1.jpg", 1);
	 hat3 = cvLoadImage("D:\\��ѧ\\�������ҵ\\FindAndHead\\Image_Hat\\hat2.jpg", 1);
	 hat4 = cvLoadImage("D:\\��ѧ\\�������ҵ\\FindAndHead\\Image_Hat\\hat3.jpg", 1);
	 hat5 = cvLoadImage("D:\\��ѧ\\�������ҵ\\FindAndHead\\Image_Hat\\hat4.jpg", 1);
	 hat6 = cvLoadImage("D:\\��ѧ\\�������ҵ\\FindAndHead\\Image_Hat\\hat5.png", 1);
	 if (!hat1)
	 {
		 printf("error2!��ȡhat1ʧ��~");
		 printf("����ñ��1����·���Ƿ���ȷ��\n");
		 exit(0);
	 }
	 if (!hat2)
	 {
		 printf("error3!��ȡhat2ʧ��~");
		 printf("����ñ��2����·���Ƿ���ȷ��\n");
		 exit(0);
	 }
	 if (!hat3)
	 {
		 printf("error4!��ȡhat3ʧ��~");
		 printf("����ñ��3����·���Ƿ���ȷ��\n");
		 exit(0);
	 }
	 if (!hat4)
	 {
		 printf("error5!��ȡhat4ʧ��~");
		 printf("����ñ��4����·���Ƿ���ȷ��\n");
		 exit(0);
	 }
	 if (!hat5)
	 {
		 printf("error6!��ȡhat5ʧ��~");
		 printf("����ñ��5����·���Ƿ���ȷ��\n");
		 exit(0);
	 }
	 if (!hat6)
	 {
		 printf("error7!��ȡhat6ʧ��~");
		 printf("����ñ��6����·���Ƿ���ȷ��\n");
		 exit(0);
	 }
}
void detect_and_draw(IplImage* img)
{
	//����ϵ��
	double scale = 1.3;
	//���廭����ɫ
	static CvScalar colors[] = { { 0,0,255 } };
	//��������������
	char* cascade_name = "D:\\gongju\\opencv3.1.0\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt2.xml";
	//char* cascade_name = "D:\\gongju\\opencv3.1.0\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0);
	//���ٹ����ڴ�
	CvMemStorage* storage = cvCreateMemStorage(0);
	//���ûҶ�ͼ������ڻҶ�ͼ�ϼ��
	IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);
	//����ͼ���С��from������
	IplImage* small_img = cvCreateImage(cvSize(round(img->width / scale), round(img->height / scale)), 8, 1);
	cvCvtColor(img, gray, CV_BGR2GRAY);
	cvResize(gray, small_img, CV_INTER_LINEAR);
	//ֱ��ͼ��һ����ȡ����㣩
	cvEqualizeHist(small_img, small_img);
	//����������ڴ�
	cvClearMemStorage(storage);
	//������⣬�����䴢����CvSeq������
	CvSeq* objects = cvHaarDetectObjects(
		small_img,
		cascade,
		storage,
		1.1,//ɨ�貽��
		3,//���óɹ���С��������
		CV_HAAR_FIND_BIGGEST_OBJECT,
		cvSize(30, 30),//������С��С
					   //cvSize(small_img->width, small_img->height)
		cvSize(500, 500));//��������С��bad
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
	//�ͷ��м�ͼ���ڴ�
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);

}
void Tohead(IplImage* img, IplImage* hat)
{
	IplImage* dst;
	//����ROI
	cvSetImageROI(img,
				  cvRect(face.point.x, face.point.y - face.height,
				  face.weight, face.height));
	//dst= cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	//����ñ�Ӵ�С
	dst = cvCreateImage(cvSize(face.weight, face.height), IPL_DEPTH_8U, 3);
	cvResize(hat, dst, CV_INTER_NN);
	//���Ի��
	cvAddWeighted(img, 0, dst, 1, 0, img);
	//�ͷ�ROI�ڴ�
	cvResetImageROI(img);
	//��ʾЧ��ͼ
	cvShowImage("Ч��ͼ", img);
}
//�洢ͼ��
void TosaveImage(IplImage* img)
{
	outText();
	//���ٶ�̬�ڴ�����û�����洢·��
	char* ss = (char*)malloc(sizeof(char) * 100);
	printf("������ͼ�񱣴�ĵ�ַ:\n");
	gets(ss);
	//ѡ�񴢴��ʽ
	int p[2];
	p[0] = CV_IMWRITE_JPEG_QUALITY;
	p[1] = 90;
	//�洢ͼ��
	cvSaveImage(ss, img, p);
	outText();
	//�洢ͼ��ɹ���ʾ��
	MessageBox(hwnd, TEXT("ͼ�񱣴����"), TEXT("���������ʾ��"), MB_OK);
	printf("ͼ�񱣴��ַΪ:\n");
	puts(ss);
	//�ͷŶ�̬�ڴ�
	free(ss);
}