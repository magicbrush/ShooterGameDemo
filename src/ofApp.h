#pragma once

#include "ofMain.h"

// 5.1.1 作用域： 4 命名空间作用域
// p214 类名的前向申明
namespace CPPClass
{
	class MovingSprite;	
}

//  4.2.1 类的定义 
class ofApp : 
	// 7.2.1 公有继承
	public ofBaseApp
{	
	// -------- shared resource： 共享资源 ----------------//
	// 关卡、角色的形象图片
	ofImage ImgLevel;
	ofImage ImgPlayer;
	ofImage ImgBullet;
	ofImage ImgEnemy1;
	ofImage ImgEnemy2;
	// 字体
	ofTrueTypeFont Font; 
	// 音乐
	ofSoundPlayer SoundBGMusic;
	// 音效
	ofSoundPlayer SoundBullet;
	ofSoundPlayer SoundLaugh;
	ofSoundPlayer SoundDie;
	ofSoundPlayer SoundMonsterDie;
	
	// ------------ 游戏中的各种对象 -----------------------//
	// level
	// 关卡信息
	bool Running; // 进行状态
	float time; // 存活时间
	int score; // 分数

	// player　玩家
	//4 命名空间作用域的访问 ::
	//6.2.11 对象指针
	CPPClass::MovingSprite* Player;	
	ofVec2f Acc; // 玩家的加速度
	
	// bullets	子弹
	// 6.4 vector容器，10.3 容器
	// 对象指针
	vector<CPPClass::MovingSprite*> Bullets;
	
	// enemy　敌人
	// 6.4 vector容器
	// 对象指针
	vector<CPPClass::MovingSprite*> Enemys;	
	
	// ------------ methods ----------------------------------//
	public:
		// 初始化
		void setup();

		// 更新
		void update();

		// 显示
		void draw();

		// 键盘触发
		void keyPressed(int key);
		void keyReleased(int key);
		
		// 鼠标触发
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		// 窗口变形
		void windowResized(int w, int h);
		
		// 文件拖入
		void dragEvent(ofDragInfo dragInfo);
		
		// 接收到ofSendMessage()发来的消息
		void gotMessage(ofMessage msg);

		// -------------辅助函数 ------------//
		// 复位游戏
		void resetGame();
		// eraseNullSprite 从序列容器中删除已经是NULL的指针
		// 3.1.3 -2 引用传递
		void eraseNullSprite( vector<CPPClass::MovingSprite*>& S );
		// clearSprites 清除序列容器中的所有内容
		// 3.1.3 -2 引用传递
		void clearSprites( vector<CPPClass::MovingSprite*>& S );
		
		// 随机生成敌人
		void randGenerateEnemy(  );
		// 玩家行动
		void updatePlayer();
		// 敌人行动		
		void updateEnemies( );
		// 子弹行动
		void updateBullets();
		// 更新生命状态
		void updateLifeStates();

		// 显示场景
		void drawLevel();

		// 玩家发射子弹到x,y
		void PlayerFireBulletTo( int x, int y );
		
		


		
};
