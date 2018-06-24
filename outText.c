#include"outText.h"
void outText(void)
{   
	//清屏
	system("cls");
	printf("             \n");
	printf("             \n");
	printf("                           opencv趣味小项目之带帽篇\n ");
    printf("------------------------------------------------------------------------------\n");
	printf("项目概述：对输入照片进行人脸识别后，自行对该人物进行带帽p图并选择是否保存，按下空格键可换帽。\n");
	printf("功能键：  \n");
	printf("	换帽:\t        空格(space)\t\n");
	printf("        更换原图片:\tq\t\n");
	printf("        退出应用程序:\tEsc\t\n");
    printf("试验平台：Opencv  VS2015\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("waring:注意输入的路径转义字符！\n");
	printf("EX:\n");
	printf("D:/大学/计算机作业/FindAndHead/Imgae_src/kayanon.jpg\n");
	printf("-------------------------------------------------------------------------------\n");
	//system("color 87");
	//绿底黄字
	system("color 3e");
}