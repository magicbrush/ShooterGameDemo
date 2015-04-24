// 避免重复包含此文件
#pragma once 

// 5.6.4 编译预处理， 防止头文件被重复包含
#ifndef $HUNTINGSPRITE_H$  
#define $HUNTINGSPRITE_H$

#include "ofMain.h"
#include "MovingSprite.h"

// 5.1.1 作用域： 4 命名空间作用域
namespace CPPClass
{	
	// 4.2.1 类的定义 
	class HuntingSprite: 
		// 7.2.1 公有继承
		public MovingSprite  
	{
	// 4.2.2 类成员的访问控制：公开
	public: 
		// 4.3.1 构造函数
		HuntingSprite(  
			MovingSprite* Target,  // 6.2.11 对象指针
			ofPoint Pos = ofPoint(0),  // 3.3 默认形参
			ofVec2f Vel = ofVec2f(0,1),  
			ofVec2f Size=ofVec2f(20,20), 
			float Agility = 1.0f, 
			ofImage* I=NULL, // 6.2.11 对象指针， p204 NULL指针
			int Score = 2);		

		//8.3.1 一般虚函数成员的重载
		virtual void update(); 

		// 4.2.2 类成员的访问控制： 私有
	private: 
		void turnToTarget();

	private:
		float agility; 
		// 6.2.11 对象指针
		MovingSprite* target; 
	};
}


#endif