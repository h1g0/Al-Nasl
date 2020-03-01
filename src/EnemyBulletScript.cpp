#include "Common.h"
/****************************************************************************************
_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

　　　　　　　　　　　　　　　　　弾幕管理実体

_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
*****************************************************************************************/

//死亡フラグ
void EBCmd::ptndead(int& idx){
	if(eb[idx].flg == 0){
		vx=0;
		vy=1;
	}
	if(My::shooting==true){
		eb[idx].snipedef(*img,*px,*py,3,0,cp);
	}else{
		vx=0;
		vy=1;
	}
}

//==========================================================================================
//Stage1弾幕記述
//==========================================================================================

//何もしない
void EBCmd::ptn100(int& idx){
	if(eb[idx].flg == 0){
		vx=0;
		vy=0;
		cp=999999999;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}

//単純な狙撃(2周目は3wayに)
void EBCmd::ptn101(int& idx){
	if(eb[idx].flg == 0){
		if(PjSys::GameLevel>0 || idx%3==0){
			cp+=10*PjSys::Hard+10;
			eb[idx].snipedef(*img,*px,*py,3.5,0,cp);
		}else if(idx%3==0){
			eb[idx].snipedef(*img,*px,*py,3.5,-10,cp);
		}else{
			eb[idx].snipedef(*img,*px,*py,3.5,-10,cp);
		}
	}
}

//単純に下に飛んでいく
void EBCmd::ptn102(int& idx){
	if(eb[idx].flg == 0){
		vx=0;
		vy=3;
		cp+=10*(PjSys::Hard/2)+10;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}

//自機狙い3way(各10度開き)
void EBCmd::ptn103(int& idx){
	if(eb[idx].flg == 0){
		int m=l++%3;
		if(m==0){
			cp+=11*PjSys::Hard+47;
			eb[idx].snipedef(*img,*px,*py,5,0,cp);
		}else if(m==1){
			eb[idx].snipedef(*img,*px,*py,3,-10,cp);
		}else{
			eb[idx].snipedef(*img,*px,*py,3,10,cp);
		}
	}
}
//回転砲塔(23度)
void EBCmd::ptn104(int& idx){
	if(eb[idx].flg == 0){
		deg+=23;
		cp+=5*PjSys::Hard;
		math m;
		vx=mysin(m.ToRadian(deg))*(2.5+0.5*(l%3));
		vy=mycos(m.ToRadian(deg))*(2.5+0.5*(l%3));
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}
//回転砲塔(10度)
void EBCmd::ptn105(int& idx){
	if(eb[idx].flg == 0){
		deg+=107.2;
		cp+=PjSys::Hard;
		math m;
		vx=mysin(m.ToRadian(deg))*3;
		vy=mycos(m.ToRadian(deg))*3;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}
//回転砲塔(-5度)
void EBCmd::ptn106(int& idx){
	if(eb[idx].flg == 0){
		deg-=7;
		cp+=3*PjSys::Hard;
		math m;
		vx=mysin(m.ToRadian(deg))*3;
		vy=mycos(m.ToRadian(deg))*3;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}
//旋回砲塔(-12.5度)
void EBCmd::ptn107(int& idx){
	if(eb[idx].flg == 0){
		deg-=102.5;
		cp+=2*PjSys::Hard;
		math m;
		vx=mysin(m.ToRadian(deg))*(2.5+0.5*(l%3));
		vy=mycos(m.ToRadian(deg))*(2.5+0.5*(l%3));
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}

//緩い旋回砲塔*4
void EBCmd::ptn108(int& idx){
	if(eb[idx].flg == 0){
		if(l++%3==0){
			deg+=103.5;
			cp+=2*PjSys::Hard;
		}
		math m;
		vx=mysin(m.ToRadian(deg))*(2.5+0.5*(l%3));
		vy=mycos(m.ToRadian(deg))*(2.5+0.5*(l%3));
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}

//狙撃
void EBCmd::ptn109(int& idx){
	if(eb[idx].flg == 0){
		if(l++%10==0){
			//deg+=123;
			cp+=PjSys::Hard*10;
		}else{cp+=2;}
		eb[idx].snipedef(*img,*px,*py,l/2,0,cp);
	}
}

//ホーミングレーザー
void EBCmd::ptn10a(int& idx){
	if(eb[idx].flg == 0){
		cp+=1;
		if(idx%20==0){cp+=40;}
		eb[idx].snipedef(*img,*px,*py,5,0,cp);
	}
	if(idx%20==0){
		if(eb[idx].phase <= 90){
			if(eb[idx].x-My::x>0.2){
				eb[idx].vx-=0.2;
			}else if(eb[idx].x-My::x<-0.2){
				eb[idx].vx+=0.2;
			}
			if(eb[idx].vx>5){eb[idx].vx=5;}else if(eb[idx].vx<-5){eb[idx].vx=-5;}

			if(eb[idx].y-My::y>0.2){
				eb[idx].vy-=0.2;
			}else if(eb[idx].y-My::y<-0.2){
				eb[idx].vy+=0.2;
			}
			if(eb[idx].vy>5){eb[idx].vy=5;}else if(eb[idx].vy<-5){eb[idx].vy=-5;}
		}
	}else{
		eb[idx].vectordef(eb[idx-1].vx,eb[idx-1].vy);
		eb[idx].x=eb[idx-1].x-eb[idx-1].vx;
		eb[idx].y=eb[idx-1].y-eb[idx-1].vy;
	}
}

//ホーミング2
void EBCmd::ptn10b(int& idx){
	int dg=20;
	if(eb[idx].flg == 0){
		math m;
		vx=m.getcos(eb[idx].x,eb[idx].y,My::x,My::y);
		vy=m.getsin(eb[idx].x,eb[idx].y,My::x,My::y);
		cp++;
		if(idx%10==0){cp+=PjSys::Hard*10;}
		eb[idx].def(*img,*px,*py,vx,vy,cp);
		eb[idx].snpdeg=m.ToDegree(PI-m.vec2rad(vx,vy));
		//srad=PI-(m.vec2rad(vx,vy)+m.ToRadian(snpdeg));
	}
	if(idx%10==0){
		math m;
		double vx2=m.getcos(eb[idx].x,eb[idx].y,My::x,My::y);
		double vy2=m.getsin(eb[idx].x,eb[idx].y,My::x,My::y);
		double diff=eb[idx].snpdeg-m.ToDegree(PI-m.vec2rad(vx2,vy2));
		/*if(abs(diff)>120){ //敵と120度以上離れてたら断念
			eb[idx].snpdeg+=0;
		}else*/ if(diff<0){ //弾の進行ベクトルが目標より左
			if(diff<dg*-1){
				eb[idx].snpdeg+=dg*1.2;
			}else{
				eb[idx].snpdeg=m.ToDegree(PI-m.vec2rad(vx2,vy2));
			}
		}else{
			if(diff>dg){
					eb[idx].snpdeg-=dg*1.2;
			}else{
				eb[idx].snpdeg=m.ToDegree(PI-m.vec2rad(vx2,vy2));
			}
		}

		vx=mycos(m.ToRadian(eb[idx].snpdeg))*4;
		vy=mysin(m.ToRadian(eb[idx].snpdeg))*4;
		eb[idx].vectordef(vx,vy);
	}else{
		eb[idx].vectordef(eb[idx-1].vx,eb[idx-1].vy);
		eb[idx].x=eb[idx-1].x-eb[idx-1].vx*4;
		eb[idx].y=eb[idx-1].y-eb[idx-1].vy*4;
	}
	//eb[idx].x+=vx;
	//eb[idx].y+=vy;
}

//ホーミング3
void EBCmd::ptn10c(int& idx){
	if(eb[idx].flg == 0){
		//if(idx%10==0){
			if(idx%2==0){
				eb[idx].snipedef(*img,*px,*py,5,120,cp);
				cp+=PjSys::Hard*5+10;
			}else{
				eb[idx].snipedef(*img,*px,*py,5,-120,cp);
				//cp++;
			}
		//}else{
			//eb[idx].def(*img,*px,*py,vx,vy,cp);
			//cp++;
		//}
	}
	//if(idx%10==0){
		if(eb[idx].phase<=30){
			if(idx%2==0){
				eb[idx].sniperedef(5,120-eb[idx].phase*4);
			}else{
				eb[idx].sniperedef(5,-120+eb[idx].phase*4);
			}
		}
	//}else{
		//	eb[idx].vectordef(tvx[1][idx%10],tvy[1][idx%10]);
		//	eb[idx].x=tx[1][idx%10];
		//	eb[idx].y=ty[1][idx%10];
//	}
	//eb[idx].x+=vx;
	//eb[idx].y+=vy;
}

//上に飛んでいく枡形
void EBCmd::ptn10d(int& idx){
	if(eb[idx].flg == 0){
		vx=0;
		vy=0;
		//cp+=4+idx%3;
		if(idx%10==0){cp+=20+PjSys::Hard*5;}
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
	if(eb[idx].phase == (idx%10)*5){
		vx=0;
		vy=-2;
		eb[idx].vectordef(vx,vy);
	}
}

//右に飛んでいく3way枡形
void EBCmd::ptn10e(int& idx){
	if(eb[idx].flg == 0){
		vx=0;
		vy=0;
		//cp+=4+idx%3;
		if(idx%10==0){cp+=30+PjSys::Hard*4;}
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
	if(eb[idx].phase == (idx%10)*2){
		//math m;
		//eb[idx].y+=cos(m.ToRadian((idx%10)*36))*30;
		vx=2;
		vy=(idx%3)-1;
		eb[idx].vectordef(vx,vy);
	}
}

//遅延型機雷
void EBCmd::ptn10f(int& idx){
	if(eb[idx].flg == 0){
		vx=0;
		vy=0;
		if(idx%20==0){cp+=10*PjSys::Hard;}
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
	if(eb[idx].phase==30){
		//if(eb[idx].y<=480 && eb[idx].y>=0 && eb[idx].x<=320 && eb[idx].x >= 120){
			math m;
			vx=mycos(m.ToRadian((idx%20)*18+(idx-idx%20)/4))*4;
			vy=mysin(m.ToRadian((idx%20)*18+(idx-idx%20)/4))*4;
			eb[idx].vectordef(vx,vy);
		//}
	}
}

//-------------------------------------------------------------------------------------------
//Stage1ボス弾幕
//-------------------------------------------------------------------------------------------
//旋回砲塔*3
void EBCmd::ptn1a1(int& idx){
	if(eb[idx].flg == 0){
		if(l++%3==0){
			deg+=153.7;
		}
		if(l%9==0){cp+=PjSys::Hard;}
		math m;
		vx=mysin(m.ToRadian(deg))*(3.2+0.9*(l%3));
		vy=mycos(m.ToRadian(deg))*(3.2+0.9*(l%3));
		eb[idx].def(*Enm::RLaser,*px,*py,vx,vy,cp);
	}
}
//V時
void EBCmd::ptn1a2(int& idx){
if(idx==0){deg=0;}
	if(eb[idx].flg == 0){
		if(idx%143==0){
			deg-=10;
			cp+=PjSys::Hard*4+10;
		}
		if(idx%8==0){
			//cp++;
			deg-=20;
		}

		math m;
		vx=mysin(m.ToRadian(180-deg-(idx%8)+90))*(4.0-0.2*abs(((idx%8)-4)+1));
		vy=mycos(m.ToRadian(180-deg-(idx%8)+90))*(4.0-0.2*abs(((idx%8)-4)+1));
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}/*else if(eb[idx].phase >= 30){
		//vx=eb[idx].vx*=-1;
		vx=eb[idx].vx*=1+0.001*abs((idx%8)-4);
		vy=eb[idx].vy*=1+0.001*abs((idx%8)-4);
		//vy=-(10-PjSys::Hard)/2;
		eb[idx].vectordef(vx,vy);
	}*/
}
//円形同心円+円に広がってから狙撃
void EBCmd::ptn1a3(int& idx){
	math m;
	if(eb[idx].flg == 0){
		if(idx%10==0){
			cp++;

			if(idx%180==0){
				//l++;
				cp+=PjSys::Hard*8;
			}
		}
		vx=mysin(m.ToRadian((idx%10)*36))*5;
		vy=mycos(m.ToRadian((idx%10)*36))*5;

		//math m;
		//RGBに固定
		if(idx%540<180){
			eb[idx].def(*Enm::RBullet,*px,*py,vx,vy,cp);
		}else if(idx%540<360){
			eb[idx].def(*Enm::GBullet,*px,*py,vx,vy,cp);
		}else{
			eb[idx].def(*Enm::BBullet,*px,*py,vx,vy,cp);
		}
	}
	if(eb[idx].phase<10){
		//36度毎に10個の弾を創出(円形の元)
		vx=mysin(m.ToRadian((idx%10)*36))*3;
		vy=mycos(m.ToRadian((idx%10)*36))*3;
		eb[idx].vectordef(vx,vy);
	}else if(eb[idx].phase<70){
		if(idx%540<180){
			vx=mysin(m.ToRadian((idx-(idx%10))*2)+90)*mysin(PI*(eb[idx].phase-10)/60)*2;
			vy=mycos(m.ToRadian((idx-(idx%10))*2)+90)*mysin(PI*(eb[idx].phase-10)/60)*2;
		}else if(idx%540<360){
			vx=mysin(m.ToRadian((idx-(idx%10))*2)+90)*mysin(PI*(eb[idx].phase-10)/60)*2;
			vy=mycos(m.ToRadian((idx-(idx%10))*2)+90)*mysin(PI*(eb[idx].phase-10)/60)*2;
		}else{
			vx=mysin(m.ToRadian((idx-(idx%10))*2)+90)*mysin(PI*(eb[idx].phase-10)/60)*2;
			vy=mycos(m.ToRadian((idx-(idx%10))*2)+90)*mysin(PI*(eb[idx].phase-10)/60)*2;
		}
		eb[idx].vectordef(vx,vy);
	}else if(eb[idx].phase<130){ //停止
		//if(idx%360<180){
			vx=mysin(m.ToRadian((idx-(idx%10))*2))*0.01;
			vy=mycos(m.ToRadian((idx-(idx%10))*2))*0.01;
		/*}else{
			vx=sin(m.ToRadian((idx-(idx%10))*2+5))*0.01;
			vy=cos(m.ToRadian((idx-(idx%10))*2+5))*0.01;
		}*/
		eb[idx].vectordef(vx,vy);
	}else if(eb[idx].phase<160){ //再送出
		if(idx%540<180){
			vx=mysin(m.ToRadian((idx-(idx%10))*2)+90)*mysin(PI*(eb[idx].phase-130)/60)*3;
			vy=mycos(m.ToRadian((idx-(idx%10))*2)+90)*mysin(PI*(eb[idx].phase-130)/60)*3;
			eb[idx].vectordef(vx,vy);
		}else if(idx%540<360){
			vx=mysin(m.ToRadian((idx%10)*36))*mysin(PI*(eb[idx].phase-130)/60)*4;
			vy=mycos(m.ToRadian((idx%10)*36))*mysin(PI*(eb[idx].phase-130)/60)*4;
			eb[idx].vectordef(vx,vy);
		}else{
			if(PjSys::Hard<4){
				eb[idx].sniperedef(5,0);
			}else{
				vx=mysin(m.ToRadian((idx-(idx%10))*2)+90)*mysin(PI*(eb[idx].phase-130)/60)*5;
				vy=mysin(PI*(eb[idx].phase-130)/60)*5;
				eb[idx].vectordef(vx,vy);
			}
		}
	}
}
//円形狙撃
void EBCmd::ptn1a4(int& idx){
	if(eb[idx].flg == 0){
		//if(deg>=45){deg=-135;}
		if(l++%20==0){
			deg+=18.1;
			cp+=4*PjSys::Hard+30;
		}else{
			deg+=18.1;
			//cp+=0;
		}
		math m;
		vx=mysin(m.ToRadian(deg))*4;
		vy=mycos(m.ToRadian(deg))*4;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
	if(PjSys::GameLevel>0 && eb[idx].phase == 20){
		eb[idx].sniperedef(4,0);
	}else if(PjSys::GameLevel==0 && eb[idx].phase == 40){
		switch(idx%3){
			case 0:
				eb[idx].sniperedef(8,0);
				break;
			case 1:
				eb[idx].sniperedef(4,20);
				break;
			case 2:
				eb[idx].sniperedef(4,-20);
				break;
		}
	}
}

//同心円→加速度落下
void EBCmd::ptn1a5(int& idx){
	if(eb[idx].flg == 0){
		//if(deg>=45){deg=-135;}
		if(l++%30==0){
			deg+=7.3;
			cp+=20*PjSys::Hard;
		}else{
			deg+=12.5;
			//cp+=0;
		}
		math m;
		vx=mysin(m.ToRadian(deg))*2;
		vy=mycos(m.ToRadian(deg))*2;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}

	if((PjSys::GameLevel>0 && eb[idx].phase >= 40) || (PjSys::GameLevel==0 && eb[idx].phase >= 80)){
		vx=eb[idx].vx*0.995;
		vy=eb[idx].vy+0.05;
		eb[idx].vectordef(vx,vy);
	}
}
//箒掃き
void EBCmd::ptn1a6(int& idx){
	if(eb[idx].flg == 0){
		//if(eb[idx].phase==0){tmp[0]=1;deg=0;}
		if(l++%5==0){
			if(deg>90){tmp[0]=-1;}else if(deg<-90){tmp[0]=1;}
			if(tmp[0]==1){deg+=5.7;}else{deg-=8.3;}
			cp+=PjSys::Hard;
		}
		math m;
		vx=mysin(m.ToRadian(deg))*(2+0.7*(l%5));
		vy=mycos(m.ToRadian(deg))*(2+0.7*(l%5));
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}

//自機狙い4way
void EBCmd::ptn1a7(int& idx){
	if(eb[idx].flg == 0){
		if(l++%2==0){
			cp+=2;
			math m;
			deg=mysin(m.ToRadian(idx*2))*9;
		}
		eb[idx].snipedef(*img,*px,*py,(8-PjSys::Hard)/2+3,-20+8*(l%4+1)+deg,cp);
	}
}
/*
//切り返し重視の同心円連射
void EBCmd::ptn1a8(int& idx){
	if(eb[idx].flg == 0){
		//if(deg>=45){deg=-135;}
		if(l++%5==0){
			deg+=5+PjSys::Hard;
			cp+=1;
		}else{
			deg+=2;
			cp+=0;
		}
		math m;
		vx=sin(m.ToRadian(deg))*2;
		vy=cos(m.ToRadian(deg))*2;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}*/

//くねくね
void EBCmd::ptn1a8(int& idx){
	if(eb[idx].flg == 0){
		if(idx%20==0){
			cp+=3;
			math m;
			deg=mysin(m.ToRadian(idx)/2)*(11-PjSys::Hard)*1.6;
		}
		math m;
		if(idx%20<15){
			vx=mysin(m.ToRadian(-24*(idx%15+1)+deg))*2;
			vy=mycos(m.ToRadian(-24*(idx%15+1)+deg))*2;
			eb[idx].def(*img,*px,*py,vx,vy,cp);
		}else{
			if(PjSys::HardConst<5){
				vx=mysin(m.ToRadian(idx*73.7))*3;
				vy=mycos(m.ToRadian(idx*73.7))*3;
			}else{
				vx=mysin(m.ToRadian(idx*72))*3;
				vy=mycos(m.ToRadian(idx*72))*3;
			}
			eb[idx].def(*Enm::BLaser,*px,*py,vx,vy,cp);
		}
		//eb[idx].snipedef(*img,*px,*py,2,90-18*(l%20+1)+deg,cp);
	}
}

//旋回砲塔→x軸のみ反転しながら下へ
void EBCmd::ptn1a9(int& idx){
	if(eb[idx].flg == 0){
		deg+=145.7;
		//cp++;
		cp++;

		if(l++%5==0){
			//deg+=9.3;
			cp+=PjSys::Hard;
		}

		math m;
		vx=mysin(m.ToRadian(deg))*3;
		vy=mycos(m.ToRadian(deg))*3;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
	if(eb[idx].phase == 20){
		//eb[idx].img=
		vx=eb[idx].vx*-1;
		vy=3;
		//vy=-(10-PjSys::Hard)/2;
		eb[idx].vectordef(vx,vy);
	}
}
//左右両側に(2周目は2wayの自機狙いに
void EBCmd::ptn200(int& idx){
	if(eb[idx].flg == 0){
		if(PjSys::GameLevel==0 && idx%10<2){
			eb[idx].snipedef(*Enm::RBullet,*px,*py,4,0,cp);
		}else if(idx%2==0){
			vx=2+(idx%10)/10;
			vy=0;
			eb[idx].def(*img,*px,*py,vx,vy,cp);
			cp+=25*(PjSys::Hard/2)+20;
		}else{
			vx=-2-(idx%10)/10;
			vy=0;
			eb[idx].def(*img,*px,*py,vx,vy,cp);
		}
		//vy=0;
	}
}

//暫くとどまる→円形にだんだん爆発
void EBCmd::ptn201(int& idx){
	if(eb[idx].flg == 0){
		vx=0;
		vy=0;
		cp+=1+PjSys::Hard;
		eb[idx].def(*Enm::RBullet,*px,*py,vx,vy,cp);
	}else{
		if(eb[idx].phase >= 60 && eb[idx].phase >= 120 ){
			math m;
			deg=idx*24.7+PjSys::Hard*3;
			vx=mycos(m.ToRadian(deg))*(eb[idx].phase-60)/30;
			vy=mysin(m.ToRadian(deg))*(eb[idx].phase-60)/30;
			eb[idx].vectordef(vx,vy);
		}
	}
}

//2面中ボス最後
void EBCmd::ptn202(int& idx){
	if(eb[idx].flg == 0){
		if(idx%5==0){
			if(idx%50==0){
				cp+=5+PjSys::Hard*5;
			}
			cp+=5;
		}

		double add=0;
		int lid=idx%50;
		//add=(NumDividable(lid,5)/5);
		add=((lid-(lid%5))/5)*(0.5+(8-PjSys::Hard)/10);
		if(lid%5==1 || lid%5==3){add+=1;}
		eb[idx].snipedef(*img,*px,*py,2+add,(idx%5)*20-40,cp);
	}
}

//サイン波同心円
void EBCmd::ptn203(int& idx){
	if(eb[idx].flg == 0){
		if(idx%180==0){cp+=20+PjSys::Hard*10;}

		double rad=(idx%180)*2*RAD;
		double scl=(idx%360<180)?(mycos(rad*6)*0.6):(mysin(rad*6)*0.6);
		if(scl<0){
			scl+=2.5;
		}else{
			scl+=1.5;
		}
		vx=mycos(rad)*scl;
		vy=mysin(rad)*scl;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}

//円形狙撃++
void EBCmd::ptn204(int& idx){
	if(eb[idx].flg == 0){
		double rad=(idx-(idx%5))*5*RAD;
		int scr=8+(idx%5)*16;
		vx=mycos(rad)*scr;
		vy=mysin(rad)*scr;
		if(idx%5==0){
			cp++;
			if(idx%360==0){
				cp+=PjSys::Hard*10;
			}
		}
		if(idx%10==4){
			eb[idx].def(*Enm::GBullet,*px,*py,vx,vy,cp);
		}else{
			eb[idx].def(*Enm::BBullet,*px,*py,vx,vy,cp);
		}
	}
	if(eb[idx].phase==2){
		vx=0;
		vy=0;
		eb[idx].vectordef(vx,vy);
	}else if(eb[idx].phase==20){
		if(PjSys::Hard<5 && idx%10==4){
			double rad=(idx-(idx%5))*5*RAD;
			int scr=2;
			vx=mycos(rad)*scr;
			vy=mysin(rad)*scr;
			eb[idx].vectordef(vx,vy);
		}else{
			eb[idx].sniperedef(5,0);
		}
	}
}

//x軸+y軸上のみ反跳
void EBCmd::ptn205(int& idx){
	if(eb[idx].flg == 0){
		int num=(8-PjSys::HardConst)*3;
		double rad=360/num*(idx%num)*RAD;
		vx=mycos(rad)*2;
		vy=mysin(rad)*2;
		if(idx%num==0){
			cp+=3;
			if(idx%(num*20)==0){
				cp+=10+PjSys::Hard*10;
			}
		}
		eb[idx].def(*Enm::BLaser,*px,*py,vx,vy,cp);
	}
	if(eb[idx].phase<=300){ //反跳
		if(eb[idx].x<=120 || eb[idx].x>=520){
			vx=eb[idx].vx*-1;
			vy=eb[idx].vy;
			eb[idx].vectordef(vx,vy);
		}
		if(eb[idx].y<=0){
			vx=eb[idx].vx;
			vy=eb[idx].vy*-1;
			eb[idx].vectordef(vx,vy);
		}
	}
}
void EBCmd::ptn206(int& idx){}
void EBCmd::ptn207(int& idx){}
void EBCmd::ptn208(int& idx){}
void EBCmd::ptn209(int& idx){}
//ワインダー
void EBCmd::ptn20a(int& idx){
	math m;
	if(eb[idx].flg == 0){
		if(idx%40==0 && PjSys::GameLevel==0){
			eb[idx].snipedef(*Enm::RLaser,*px,*py,4,(idx%160)/5-6,cp);
		}else{
			if(++l%10==0){cp+=2;l=0;}
			deg=20*l;
			double add=mysin(m.ToRadian(idx)/10)*(15+(8-PjSys::Hard)*2);
			vx=mycos(m.ToRadian(deg+add))*5;
			vy=mysin(m.ToRadian(deg+add))*5;
			eb[idx].def(*img,*px,*py,vx,vy,cp);
		}
	}
}

//円形の弾をばらまく同心円
void EBCmd::ptn20b(int& idx){
	math m;
	if(eb[idx].flg == 0){
		if(idx%180==0){
			//l++;
			cp+=PjSys::Hard*6+50;
		}
		vx=mysin(m.ToRadian((idx%10)*36))*5;
		vy=mycos(m.ToRadian((idx%10)*36))*5;

		//math m;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
		if(eb[idx].phase<10){
			vx=mysin(m.ToRadian((idx%10)*36))*5;
			vy=mycos(m.ToRadian((idx%10)*36))*5;
		}else{
			vx=mysin(m.ToRadian((idx-(idx%10))*2))*3;
			vy=mycos(m.ToRadian((idx-(idx%10))*2))*3;
		}
		eb[idx].vectordef(vx,vy);
}

//くねくね2
void EBCmd::ptn20c(int& idx){
	if(eb[idx].flg == 0){
		if(idx%12==0){
			//if(idx%(60*(8-PjSys::HardConst))==0){cp+=100;}

			cp+=3;
			math m;
			deg=mysin(m.ToRadian(idx)/2)*15;
			//if(abs(deg)>=PjSys::HardConst && abs(deg)<=PjSys::HardConst*2){deg=0;}
		}
		math m;
		if(deg>=-PjSys::HardConst && deg<=PjSys::HardConst){
			vx=1000;
			vy=1000;
		}else{
			if(idx%2==0){
				vx=mysin(m.ToRadian(30*(idx%12+1)+deg))*2;
				vy=mycos(m.ToRadian(30*(idx%12+1)+deg))*2;
			}else{
				vx=mysin(m.ToRadian(30*(idx%12+1)-deg))*2;
				vy=mycos(m.ToRadian(30*(idx%12+1)-deg))*2;
			}
		}
		eb[idx].def(*img,*px,*py,vx,vy,cp);

		//eb[idx].snipedef(*img,*px,*py,2,90-18*(l%20+1)+deg,cp);
	}
}

//下へ(斑鳩C3中ボス風味)
void EBCmd::ptn20d(int& idx){
	if(eb[idx].flg == 0){
		if(idx%((8-PjSys::Hard)*5)==0){
			//l++;
			cp+=PjSys::Hard*5;
		}else if(idx%2==0){cp+=2;}
		vx=0;
		if(idx%2==0){vy=3;}else{vy=-3;}
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}else{
		/*
		if(eb[idx].phase<=60){
			vx=0;
			if(idx%2==0){vy=eb[idx].vy+(idx%((7-PjSys::Hard)*10))*0.0001;}else{vy=eb[idx].vy-(idx%((7-PjSys::Hard)*10))*0.0001;}
			eb[idx].vectordef(vx,vy);
		}
		*/
	}
}
//とどまる→円形に爆発(ボスver)
void EBCmd::ptn20e(int& idx){
	if(eb[idx].flg == 0){
		vx=0;
		vy=0;
		cp+=PjSys::Hard;
		if(idx%10==0){
			cp+=PjSys::Hard*5;
		}
		eb[idx].def(*Enm::RBullet,*px,*py,vx,vy,cp);
	}else{
		if(eb[idx].phase >= 60 && eb[idx].phase >= 120 ){
			math m;
			deg=idx*24.7+PjSys::Hard*3;
			vx=mycos(m.ToRadian(deg))*(eb[idx].phase-60)/60;
			vy=mysin(m.ToRadian(deg))*(eb[idx].phase-60)/60;
			eb[idx].vectordef(vx,vy);
		}
	}
}

//同心円
void EBCmd::ptn20f(int& idx){
	if(eb[idx].flg == 0){
		int num=(8-PjSys::Hard)*3;
		double rad=360/num*(idx%num)*RAD;
		vx=mycos(rad)*1;
		vy=mysin(rad)*1;
		if(idx%num==0){
		cp+=10+PjSys::Hard*20;
		}
		eb[idx].def(*Enm::RLaser,*px,*py,vx,vy,cp);
	}
}
//時期狙いバラマキ
void EBCmd::ptn300(int& idx){
	if (eb[idx].flg == 0){
		if (l++ % 20 == 0){
			//deg+=123;
			cp += PjSys::Hard * 10;
		}
		else{ cp += 2; }
		int r = GetRand(20) - 10;
		eb[idx].snipedef(*img, *px, *py, 1+(l%20)*0.25, r, cp);
	}
}
void EBCmd::ptn301(int& idx){}
void EBCmd::ptn302(int& idx){}
void EBCmd::ptn303(int& idx){}
void EBCmd::ptn304(int& idx){}
void EBCmd::ptn305(int& idx){}
void EBCmd::ptn306(int& idx){}
void EBCmd::ptn307(int& idx){}
void EBCmd::ptn308(int& idx){}
void EBCmd::ptn309(int& idx){}

//3麺中ボス弾幕下へ断続的に
void EBCmd::ptn30a(int& idx){
	if(eb[idx].flg == 0){
		if(idx%18==0){
			//l++;
			cp+=PjSys::Hard*6+30;
		}
		vx=mysin(RAD*(idx%18)*20)*(2+(8-PjSys::Hard)/3);
		vy=mycos(RAD*(idx%18)*20)*(2+(8-PjSys::Hard)/3);

		//math m;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}else{
		if(eb[idx].phase<10){
			vx=mysin(RAD*(idx%18)*20)*(2+(8-PjSys::Hard)/3);
			vy=mycos(RAD*(idx%18)*20)*(2+(8-PjSys::Hard)/3);
		}else if(eb[idx].phase == 10){
			vx=0;
			vy=0;
		}else if(eb[idx].phase > 10){
			vy = eb[idx].vy + 0.04;
			vx=0;
		}

		eb[idx].vectordef(vx,vy);
	}

	/*
	if(eb[idx].flg == 0){
		vx=0;
		vy=3;
		cp+=3;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
	*/
}
//3麺中ボス弾幕下へ断続的に2
void EBCmd::ptn30b(int& idx){
	if(eb[idx].flg == 0){
		if(idx%18==0){
			int interval = PjSys::Hard*6+30;
			if(idx == 0){
				cp+=static_cast<int>(interval/2);
			}else{
				cp+=interval;
			}
		}
		vx=mysin(RAD*(idx%18)*20)*(2+(8-PjSys::Hard)/3);
		vy=mycos(RAD*(idx%18)*20)*(2+(8-PjSys::Hard)/3);

		//math m;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}else{
		if(eb[idx].phase<10){
			vx=mysin(RAD*(idx%18)*20)*(2+(8-PjSys::Hard)/3);
			vy=mycos(RAD*(idx%18)*20)*(2+(8-PjSys::Hard)/3);
		}else if(eb[idx].phase == 10){
			vx=0;
			vy=0;
		}else if(eb[idx].phase > 10){
			vy = eb[idx].vy + 0.04;
			vx=0;
		}

		eb[idx].vectordef(vx,vy);
	}

}

//速度差自機狙い5way線弾
void EBCmd::ptn30c(int& idx){
	if(eb[idx].flg == 0){
		if(idx%50==0){cp+=PjSys::Hard * 10 + 30;}
		double vel = 1 + ((idx%50) - (idx%5))*0.02;
		eb[idx].snipedef(*img,*px,*py,vel,-36+(idx%5)*18,cp);
		//eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}

//時間差5way
void EBCmd::ptn30d(int& idx){
	if(eb[idx].flg == 0){
		if(idx%100==0){cp+=PjSys::Hard * 5 + 20;}
		if(idx%5==0){cp+=5;}
		vx = mycos((54+(idx%5)*18)*RAD)*2;
		vy = mysin((54+(idx%5)*18)*RAD)*2;

		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}


}
//旋回砲塔*4
void EBCmd::ptn30e(int& idx){
	if(eb[idx].flg == 0){
		if(idx%4==0){cp+=PjSys::Hard*5;}
		double lrad = idx*91.5; 
		vx = mycos(lrad*RAD)*1.5;
		vy = mysin(lrad*RAD)*1.5;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}
}
//旋回砲塔*4 逆回り
void EBCmd::ptn30f(int& idx){
	if(eb[idx].flg == 0){
		if(idx%4==0){cp+=PjSys::Hard*5;}
		double lrad = idx*88.5; 
		vx = mycos(lrad*RAD)*1.5;
		vy = mysin(lrad*RAD)*1.5;
		eb[idx].def(*img,*px,*py,vx,vy,cp);
	}


}

//3ボス弾幕

//旋回砲塔*2
void EBCmd::ptn3a0(int& idx){
	if (eb[idx].flg == 0){
		if (idx % 18 == 0){
			cp += PjSys::Hard ;
			deg += 25;
		}
		if (idx % 18 < 9){
			double v;
			if (idx % 9 < 3){
				v = 1.5;
			}
			else if (idx % 9 < 6){
				v = 2;
			}
			else{
				v = 2.5;
			}
			vx = mycos((deg+(8-PjSys::Hard) + (idx % 3)*2)*RAD)*v;
			vy = mysin((deg + (8 - PjSys::Hard) + (idx % 3) * 2)*RAD)*v;
			eb[idx].def(*Enm::BBullet, *px, *py, vx, vy, cp);

		}
		else{
			double v;
			if (idx % 9 < 3){
				v = 2;
			}
			else if (idx % 9 < 6){
				v = 2.5;
			}
			else{
				v = 3;
			}

			vx = mycos(((180-deg) + (idx % 3)*2)*RAD)*v;
			vy = mysin(((180-deg) + (idx % 3)*2)*RAD)*v;
			eb[idx].def(*Enm::RBullet, *px, *py, vx, vy, cp);

		}
	}
	/*
	else{
		if (idx % 6>=3 && eb[idx].y >= 430){
			if (eb[idx].vy > -1.9){
				vx = eb[idx].vx*0.9999;
				vy = eb[idx].vy - 0.05;
				eb[idx].vectordef(vx,vy);
			}
			else if (eb[idx].vy<-2.1){
				vx = eb[idx].vx*0.9999;
				vy = eb[idx].vy + 0.05;
				eb[idx].vectordef(vx, vy);

			}
		}
	}
	*/
}

//バラマキ→下に落下+円弾→下に落下
void EBCmd::ptn3a1(int& idx){

	if (eb[idx].flg == 0){
		if (idx % ((10 - PjSys::Hard) * 10 + 36) < (10 - PjSys::Hard) * 10){
			if (idx % ((10 - PjSys::Hard) * 10) == 0){
				cp += 120 + PjSys::Hard * 10;
			}
			deg = GetRand(360);
			cp += 2;
			vx = mycos(deg *RAD)*(1.0+GetRand(300) / 100.0);
			vy = mysin(deg*RAD)*(1.0+GetRand(300) / 100.0);
			switch (GetRand(1)){
			case 0:
				eb[idx].def(*Enm::BBullet, *px, *py, vx, vy, cp);
				break;
			case 1:
				eb[idx].def(*Enm::GBullet, *px, *py, vx, vy, cp);
				break;
			default:
				eb[idx].def(*Enm::GBullet, *px, *py, vx, vy, cp);
			}
		}
		else{
			vx = mycos(idx*10 *RAD)*2;
			vy = mysin(idx*10*RAD)*2;
			eb[idx].snipedef(*Enm::RBullet, *px, *py, 1.0, (idx%36)*10, cp);
		}


	}

	else{
		if (eb[idx].phase >= 60 && eb[idx].phase<120){
				vx = eb[idx].vx*0.9;
				vy = eb[idx].vy*0.9;
				eb[idx].vectordef(vx, vy);
		}
		else if (eb[idx].phase >= 120){
			vx = 0;
			vy = eb[idx].vy+=0.05;
			if (vy>4.0){ vy = 4.0; }
			eb[idx].vectordef(vx, vy);
		}
	}


}

//同心円弾+自機狙いバラマキ
void EBCmd::ptn3a2(int& idx){
	if (eb[idx].flg == 0){
		if (idx % 144 < 108){
			if (idx % 144 == 0){
				cp += 40 + PjSys::Hard * 5;
			}
			if (idx % 36 == 0){
				cp += (8-PjSys::Hard) * 2;
			}

			eb[idx].snipedef(*Enm::BBullet, *px, *py, 1.5, (idx % 36) * 10, cp);
		}
		else{
			if (idx % 144 == 108){
				cp += 40 + PjSys::Hard * 5;
			}
			double d = 15.0 - GetRand(300) / 10.0;
			double s = 1.0 + GetRand(300) / 100.0;
			eb[idx].snipedef(*Enm::GLaser, *px, *py, s, d, cp);
		}
	}

}

//速度差6way*2
void EBCmd::ptn3a3(int& idx){
	if (eb[idx].flg == 0){
		if (idx % 360 < 144){
			if (idx % 144 == 0){
				cp += PjSys::Hard * 4;
				deg += 30;
			}
			if (idx % 6 == 0){ cp ++; }
			deg += 60.3;

			vx = mycos(deg *RAD) * 1.5;
			vy = mysin(deg*RAD) * 1.5;

			eb[idx].def(*Enm::BBullet , *px, *py, vx, vy, cp);
		}
		else if (idx % 360<288){
			if (idx % 144 == 0){
				cp += PjSys::Hard*4 ;
				deg -= 30;
			}
			if (idx % 6 == 0){ cp ++; }
			deg -= 60.2;

			vx = mycos(deg *RAD) * 2;
			vy = mysin(deg*RAD) * 2;

			eb[idx].def(*Enm::RBullet, *px, *py, vx, vy, cp);

		}
		else{
			vx = mycos(5 * (idx % 72) *RAD) * (1 + (idx % 2)/2);
			vy = mysin(5 * (idx % 72)*RAD) * (1 + (idx % 2)/2);

			eb[idx].def(*Enm::GBullet, *px, *py, vx, vy, cp);

		}
	}

}
//同心円弾+自機狙いバラマキ2

void EBCmd::ptn3a4(int& idx){

	if (eb[idx].flg == 0){
		if (idx % 72 < 36){
		eb[idx].snipedef(*Enm::BBullet, *px, *py, 1.5, (idx % 36) * 10, cp);
		}
		else{
			cp +=PjSys::Hard;
			double d = (10 - PjSys::Hard) * 3 - GetRand((10 - PjSys::Hard) * 60) / 10.0;
			double s = 1.0 + GetRand(100+(8 - PjSys::Hard)*50) / 100.0;
			eb[idx].snipedef(*Enm::GLaser, *px, *py, s, d, cp);
		}
	}


}
void EBCmd::ptn3a5(int& idx){}
void EBCmd::ptn3a6(int& idx){}
void EBCmd::ptn3a7(int& idx){}
void EBCmd::ptn3a8(int& idx){}
void EBCmd::ptn3a9(int& idx){}

//=============================================
//  後で使う弾幕集
//==============================================