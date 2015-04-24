#include "HuntingSprite.h"

// 5.1.1 作用域： 4 命名空间作用域
// p21 using namespace
using namespace CPPClass; 

//p117 组合类构造函数定义的一般形式
CPPClass::HuntingSprite::HuntingSprite( 
	MovingSprite* Target, 
	ofPoint Pos /*= ofPoint(0)*/, 
	ofVec2f Vel /*= ofVec2f(0,1)*/,
	ofVec2f Size/*=ofVec2f(20,20)*/,
	float Agility /*= 1.0f*/, 
	ofImage* I/*=NULL*/,
	int Score /*= 2*/ ) :
	MovingSprite(Pos,Vel,Size,I,Score),
	target(Target),
	agility(Agility)
{}

void CPPClass::HuntingSprite::update()
{
	if(target!=NULL)
	{		
		// 让速度产生变化，速度向着目标偏转		
		turnToTarget();
	}
	// 7.5.1作用域分辨符:: 这里用于访问基类的函数update()
	MovingSprite::update();
}

void CPPClass::HuntingSprite::turnToTarget()
{
	// 6.2.11-1 ->运算符
	ofPoint PTarget = target->getPosition();
	ofPoint PSelf = getPosition();

	ofVec2f IToTarget = PTarget-PSelf; // IToTarget：从this到目标的矢量
	// 归一化为：从this到目标的单位矢量
	IToTarget.normalize(); 
	// V: 速度矢量
	ofVec2f V = getVelocity(); 
	// VNorm: 速度的单位矢量
	ofVec2f VNorm = V.normalized(); 
	//DVel： 速度的改变量： 正比于agility和矢量(IToTarget - VNorm)
	ofVec2f DVel = 0.5f*agility*(IToTarget - VNorm); 
	// 速度变化
	V += DVel;
	setVelocity(V);
}
