// 避免重复包含此文件
#pragma once 
// 5.6.4 编译预处理， 防止头文件被重复包含
#ifndef $SPRITE_H$
#define $SPRITE_H$

#include "ofMain.h"

// 5.1.1 作用域： 4 命名空间作用域
namespace CPPClass
{
	// 4.2.1 类的定义 
	class MovingSprite
	{
	// 4.2.2 类成员的访问控制：公开
	public:
		// 4.3.1 构造函数		
		MovingSprite(
			ofPoint Pos = ofPoint(0), // 3.3 默认形参
			ofVec2f Vel = ofVec2f(0,1), 
			ofVec2f Size=ofVec2f(20,20),  
			ofImage* I=NULL, // 6.2.11 对象指针
			int Score = 1);
		
		// 8.3.1 一般虚函数成员
		// draw() 显示
		virtual void draw();
		// update() 更新
		virtual void update();
		// getScore() 分值
		int getScore();
		
		// 位置的设置和获取
		void setPosition(ofPoint P);
		ofPoint getPosition();		
		ofRectangle getRect();// 获得所在的矩形范围
		
		// 移动一个位移 Trans
		void move(ofVec2f Trans);	

		// 速度的变化：
		void setVelocity(ofVec2f v);
		ofVec2f getVelocity();
		void accelerate(ofVec2f acc);
		void resist(float r = 0.99f);
	
		// getSize()/setSize() 获得/设置长宽尺寸
		ofVec2f getSize();
		void setSize(ofVec2f s);
		// getImage()：获得形象
		ofImage* getImage();
		
	// 4.2.2 类成员的访问控制： 私有
	private:
		// pos 位置
		ofPoint pos;
		// velocity 速度
		ofVec2f velocity;
		// size 长宽尺寸
		ofVec2f size;	
		// img 外貌
		// 6.2.11 对象指针
		ofImage* img;
		// score 分值
		int score;
	};
}


#endif