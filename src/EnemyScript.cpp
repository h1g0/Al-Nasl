#include "Common.h"
/****************************************************************************************
_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

				 敵移動管理実体

_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
*****************************************************************************************/

//敵死亡時の動作
void Enemy::ptndead(int &idx){
	//=====================
	//	敵死亡時に敵弾をアイテムに変換する
	//=====================
	//eb1[idx].dead=1;

	vx[idx]=0;
	vy[idx]=1;
}

//左から右へ→右から左へ
void Enemy::ptn10(int& idx){
	if(phase[idx]<2){
		vx[idx]=6;
		vy[idx]=1.5;
	//}else if(phase[idx]>50 && phase[idx]<80){
	//	vx[idx]=sin(RAD*(phase[idx]-50)*12*1.5)*7;
	//	vy[idx]=cos(RAD*(phase[idx]-50)*12)*7;
	}else{
		vx[idx]-=0.06;
		vy[idx]=1.5;
	}
}
//右から左へ→左から右へ
void Enemy::ptn11(int& idx){
	if(phase[idx]<5){
		vx[idx]=-6;
		vy[idx]=1.5;
	}else{
		vx[idx]+=0.06;
	}
}
//真下へ→しばらく停滞→上へ
void Enemy::ptn12(int& idx){
	if(phase[idx]<1){
		vx[idx]=0;
		vy[idx]=10;
	}else if(phase[idx]<13){
		vy[idx]+=0.04;
	}else if(phase[idx]<25){
		vy[idx]-=0.87;
	}else if(phase[idx]<210){
		vy[idx]=0.001;
	}else if(phase[idx]<300){
		vx[idx]=mycos(PI/90*(phase[idx]-165))*0.1;
		vy[idx]=mysin(PI/90*(phase[idx]-165))*0.1;
	}else{
		vy[idx]-=0.1;
	}
}

//真下へ→停止→下へ
void Enemy::ptn13(int& idx){
	if(phase[idx]<1){
		vx[idx]=0;
		vy[idx]=10;
	}else if(phase[idx]<13){
		vy[idx]+=0.2;
	}else if(phase[idx]<25){
		vy[idx]-=0.82;
	}else if(phase[idx]<150){
		vy[idx]=0.001;
	}else{
		vy[idx]+=0.1;
	}
}
//サイン波
void Enemy::ptn14(int& idx){
	if(phase[idx]<5){
		vx[idx]=0;
		vy[idx]=2;
	}else{
		x[idx]=320+mysin(y[idx]/50)*100;
	}
}
//サイン波(逆)
void Enemy::ptn15(int& idx){
	if(phase[idx]<1){
		vx[idx]=0;
		vy[idx]=2;
	}else{
		x[idx]=320-mysin(y[idx]/50)*100;
	}
}
//下へ→左へ
void Enemy::ptn16(int& idx){
	if(phase[idx]<1){
		vx[idx]=0;
		vy[idx]=4;
	}else if(phase[idx]<25){
		vy[idx]+=0.03;
	}else if(phase[idx]<50){
		vy[idx]-=0.12;
	}else if(phase[idx]<200){
		vy[idx]=0.001;
	}else{
		vx[idx]-=0.04;
	}
}
//下へ→右へ
void Enemy::ptn17(int& idx){
	if(phase[idx]<1){
		vx[idx]=0;
		vy[idx]=1;
	}else if(phase[idx]<25){
		vy[idx]+=0.02;
	}else if(phase[idx]<500){
		vy[idx]-=0.12;
	}else if(phase[idx]<200){
		vy[idx]=0.001;
	}else{
		vx[idx]+=0.04;
	}
}
//左から右へ加速しながら
void Enemy::ptn18(int& idx){
	if(phase[idx]<5){
		vx[idx]=0;
		vy[idx]=2;
	}else{
		vx[idx]+=0.03;
	}
}
//右から左へ加速しながら
void Enemy::ptn19(int& idx){
	if(phase[idx]<5){
		vx[idx]=0;
		vy[idx]=2;
	}else{
		vx[idx]-=0.03;
	}
}//1ボスの動き
void Enemy::ptn1a(int& idx){
	//math m;

	vx[idx]=mycos(RAD*phase[idx]/3)*0.5;
	vy[idx]=mysin(RAD*phase[idx])*0.2;
	deg[idx]=(float)(mycos(RAD*phase[idx]/3)*30*RAD);

	if(mphase[idx]>0 && mphase[idx]<=30){
		vy[idx]+=mycos(RAD*mphase[idx]*6)*-4;
		//z[idx]-=(float)(cos(RAD*mphase[idx]*12)*-0.2);
		mphase[idx]++;
	}
}
void Enemy::ptn1b(int& idx){
		vx[idx]=0;
		vy[idx]=-4;
}

//ミサイル
void Enemy::ptn1c(int& idx){
	math m;
	double tx , ty ,rad,trad;
	if(phase[idx]<5){
		if(phase[idx]==1){
				PlaySoundMem(sndSE[0],DX_PLAYTYPE_BACK,true);
		}
		tx = My::x - x[idx];
		ty = My::y - y[idx];
		rad=m.vec2rad(tx,ty)-RIGHT_ANGLE;
		if(rad>=PI*2){rad-=PI*2;}
		if(rad<=PI*-2){rad+=PI*2;}

		vx[idx]=mycos(rad)*7;
		vy[idx]=mysin(rad)*7;
		z[idx]=0.6f-phase[idx]*0.01f;
		//deg[idx]=rad;
	}else if(phase[idx]<=120){
		if(phase[idx]<=20){z[idx]=0.6f-phase[idx]*0.01f;}
		//tx,ty 本来進むべき方向、rad:現在の角度、trad:目標とすべき角度
		rad=deg[idx]-1.570796;
		if(rad>=PI*2){rad-=PI*2;}
		if(rad<=PI*-2){rad+=PI*2;}

		//if(phase[idx]%4==0){
			tx = (My::x-x[idx]);
			ty = (My::y-y[idx]);
			trad=m.vec2rad(tx,ty)-RIGHT_ANGLE;
		if(trad>=PI*2){trad-=PI*2;}
		if(trad<=PI*-2){trad+=PI*2;}

			// 外積は左右判定用、
			double v=tx * vy[idx] - ty * vx[idx]; //外積
			double lim=(1.5)*RAD; //角度上限
			double dif=abs(rad-trad); //角度差算出
			if( v < 0 ){
				(dif<lim)?rad+=dif : rad+= lim;
			}else{
				(dif<lim)?rad-=dif : rad-= lim;
			}
		//}
		vx[idx]=mycos(rad)*6;
		vy[idx]=mysin(rad)*6;
	}

	int imgid=(int)(phase[idx]/8)%4;
	DrawRotaGraph((int)(x[idx]-vx[idx]*8),(int)(y[idx]-vy[idx]*8),1.0f,deg[idx],Enm::imgAB[imgid],TRUE);
}
//下へ
void Enemy::ptn1d(int& idx){
		vx[idx]=0;
		vy[idx]=2.5+mphase[idx]/(6+PjSys::Hard*0.5);
		/*
		if(PjSys::GameLevel==0){
			switch(idx%3){
				case 1:
					vx[idx]+=-sin(phase[idx]*RAD);
					vy[idx]+=cos(phase[idx]*RAD);
					break;
				case 2:
					vx[idx]-=-sin(phase[idx]*RAD);
					vy[idx]-=cos(phase[idx]*RAD);
					break;
			}
		}
		*/
}
//右へ
void Enemy::ptn1e(int& idx){
		vx[idx]=1.5;
		vy[idx]=0;
}
//左へ
void Enemy::ptn1f(int& idx){
		vx[idx]=-2;
		vy[idx]=0;
}
//円を描いてみる
void Enemy::ptn20(int& idx){
	math m;

	vx[idx]=mysin(m.ToRadian(phase[idx]))*2;
	vy[idx]=mycos(m.ToRadian(phase[idx]))*2;
}
void Enemy::ptn21(int& idx){
	math m;
	x[idx]=320+mycos(m.ToRadian(phase[idx]+mphase[idx]))*180*mysin(m.ToRadian(phase[idx]/1.5));
	y[idx]=phase[idx]+mysin(m.ToRadian(phase[idx]+mphase[idx]))*180*mysin(m.ToRadian(phase[idx]/1.5));
}
//指定された角度へ加速しながら
void Enemy::ptn22(int& idx){
	math m;
	if(phase[idx]<=30){
		vx[idx]=mycos(m.ToRadian(mphase[idx]))*phase[idx]/10;
		vy[idx]=mysin(m.ToRadian(mphase[idx]))*phase[idx]/10;
	}
}
//指定された角度へ高速で加速しながら
void Enemy::ptn23(int& idx){
	math m;
	if(phase[idx]<=30){
		vx[idx]=mycos(m.ToRadian(mphase[idx]))*phase[idx]/4;
		vy[idx]=mysin(m.ToRadian(mphase[idx]))*phase[idx]/4;
	}
}
//左上へ高速
void Enemy::ptn24(int& idx){
	if(phase[idx]<=10){
		vx[idx]=-12;
		vy[idx]=-8;
	}else{
		expansion[idx]*=0.98f;
		vy[idx]+=0.1;
		vx[idx]+=0.14;
	}
	if(vx[idx]>0){
		x[idx]+=1000;
	}
}
//右上へ高速
void Enemy::ptn25(int& idx){
	if(phase[idx]<=10){
		vx[idx]=16;
		vy[idx]=-8;
	}else{
		expansion[idx]*=0.98f;
		vy[idx]-=0.1;
		vx[idx]-=0.14;
	}
	if(vx[idx]<0){
		x[idx]-=1000;
	}
}
//円形で突っ込んでくる→真ん中を通る
void Enemy::ptn26(int& idx){
	math m;
	if(phase[idx]<10){
		x[idx]=mycos(m.ToRadian(mphase[idx]))*350+320;
		y[idx]=mysin(m.ToRadian(mphase[idx]))*350+240;
		vx[idx]=0;
		vy[idx]=0;
	}else if(phase[idx]<150){
		vx[idx]=mycos(m.ToRadian(mphase[idx]))*(phase[idx]-10)/-20;
		vy[idx]=mysin(m.ToRadian(mphase[idx]))*(phase[idx]-10)/-20;
	}
}

//早回し
void Enemy::ptn27(int& idx){
	math m;
	if(phase[idx]<120){
		x[idx]=mphase[idx];
		y[idx]=-64;
		vx[idx]=m.getcos(x[idx],y[idx],My::x,My::y)*6;
		vy[idx]=m.getsin(x[idx],y[idx],My::x,My::y)*6;
	}
}

void Enemy::ptn28(int& idx){}
void Enemy::ptn29(int& idx){}

//2面中ボスの動き
void Enemy::ptn2a(int& idx){
	deg[idx]=0;
	if(phase[idx]<250){
		vx[idx]=0;
		vy[idx]=1.0;
	}else if(phase[idx]<350){
		vx[idx]-=0.02;
		vy[idx]-=0.01;
	}else if(phase[idx]<380){
		vx[idx]=-2;
		vy[idx]=0;
	}else if(phase[idx]<500){
		vx[idx]+=0.02;
		vy[idx]-=0.01;
	}else if(phase[idx]<650){
		vx[idx]=0;
		vy[idx]=-1;
	}else if(phase[idx]<750){
		vx[idx]+=0.02;
		vy[idx]+=0.02;
	}else if(phase[idx]<850){
		vx[idx]-=0.02;
		vy[idx]=0;
	}else if(phase[idx]<1300){
		vx[idx]=0;
		vy[idx]=0;
	}else if(phase[idx]<1400){
		vx[idx]=0;
		vy[idx]+=0.02;
	}else if(phase[idx]<1500){
		vx[idx]-=0.015;
		vy[idx]-=0.02;
	}else if(phase[idx]<1600){
		vx[idx]+=0.015;
		vy[idx]=0;
	}else if(phase[idx]<2200){ //ワインダー停止
		int lphase=phase[idx]-1600;//0<lphase<600
		double rad=(lphase*3/5+360)*RAD; //0<rad<2pi
		vx[idx]=mysin(rad)*-0.25;
		vy[idx]=mycos(rad/2)*0.05;
	}else if(phase[idx]<2230){
		vx[idx]-=0.24;
		vy[idx]-=0.1;
	}else if(phase[idx]<2290){
		vx[idx]+=0.12;
		vy[idx]+=0.1;
	}else if(phase[idx]<2380){
		vx[idx]=0;
		vy[idx]-=0.1;
	}else if(phase[idx]<2395){
		vx[idx]=0;
		vy[idx]+=4;
	}else if(phase[idx]<2410){
		vx[idx]=0;
		vy[idx]-=4;
	}else if(phase[idx]<2460){
		vx[idx]=0;
		vy[idx]=0;
	}else if(phase[idx]<2490){
		vx[idx]+=0.12;
		vy[idx]-=0.06;
	}else if(phase[idx]<2550){
		vx[idx]-=0.06;
		vy[idx]+=0.03;
	}else if(phase[idx]<2600){
		vx[idx]=0;
		vy[idx]=0;
	}else if(phase[idx]<2660){
		vx[idx]+=0.06;
		vy[idx]=0;
	}else if(phase[idx]<2780){
		vx[idx]-=0.03;
		vy[idx]-=0.05;
	}else if(phase[idx]<2900){
		vx[idx]-=0.03;
		vy[idx]+=0.05;
	}else if(phase[idx]<3020){
		vx[idx]+=0.03;
		vy[idx]+=0.05;
	}else if(phase[idx]<3140){
		vx[idx]+=0.05;
		vy[idx]-=0.05;
	}else if(phase[idx]<3200){
		vx[idx]-=0.05;
		vy[idx]=0;
	}else if(phase[idx]<3220){
		vx[idx]=0;
		vy[idx]+=0.05;
	}else if(phase[idx]<3280){
		vx[idx]=0;
		vy[idx]-=0.05;
	}else if(phase[idx]<3360){
		vx[idx]=0;
		vy[idx]+=0.05;
	}else if(phase[idx]<3380){
		vx[idx]=0;
		vy[idx]-=0.05;
	}else if(phase[idx]<3390){
		vx[idx]=0;
		vy[idx]-=6;
	}else if(phase[idx]<3400){
		vx[idx]=0;
		vy[idx]+=6;
	}else if(phase[idx]<3465){
		vx[idx]-=0.07;
		vy[idx]=0;
	}else if(phase[idx]<3510){
		vx[idx]+=0.07;
		vy[idx]=0;
	}else if(phase[idx]<3520){
		vx[idx]=0;
		vy[idx]=0;
	}else if(phase[idx]<3550){
		vx[idx]=0;
		vy[idx]+=0.2;
	}else if(phase[idx]<3580){
		vx[idx]=0;
		vy[idx]-=0.2;
	}else if(phase[idx]<4200){
		vx[idx]=0;
		vy[idx]=0;
	}else{
		//vx[idx]+=0.1;
		if(PjSys::HardConst<4){
			vx[idx]-=0.05;
			vy[idx]+=0.05;
		}else{
			//vy[idx]+=0.05;
			vx[idx]-=0.05;
		}
	}
	if(bephase==1){
		hp[idx]=0;
		IsHitBlt[idx]=false;
		IsHitPlayer[idx]=false;
	}
}
//2中ボスが死んだ時
void Enemy::ptn2b(int& idx){
	math m;
	if(phase[idx]%16==0){
		RegistExp(m.irand((int)x[idx]-60,(int)x[idx]+60),m.irand((int)y[idx]-60,(int)y[idx]+60),1.0,m.irand(0,15));
	}
	vx[idx]=0+mphase[idx];
	vy[idx]=5+mphase[idx]/10;
	expansion[idx]*=0.999f;
	z[idx]+=0.002f;
	if(bephase==1 ){
		if(mphase[idx]==0 && y[idx]>600){
			bephase=2;
			y[idx]+=100;
			eb1[idx].init();
		}
	}
}
//2ボス
void Enemy::ptn2c(int& idx){
  int FirstPhase=180;  //最初に突っ込んでくる演出にかける時間
  int CenterX=320; //中心X
  int CenterY=120;  //中心Y
  int CircleMax=0; //回転半径
  double rad; //角度
  if(phase[idx]<=FirstPhase){
	rad=-90*RAD;
	/*最初ベジェ曲線で*/
	//始点
	int sx=CenterX;
	int sy=-128;
	//制御点
	int cx=320;
	int cy=760;
	//終点
	int ex=(int)(CenterX+mycos(rad)*CircleMax);
	int ey=(int)(CenterY+mysin(rad)*CircleMax);
	Get2DBezier(sx,sy,ex,ey,cx,cy,FirstPhase,phase[idx],&x[idx],&y[idx]);
  }else{
	rad=(phase[idx])*RAD;
	double addx=mycos(rad*0.5)*32;
	double addy=mysin(rad)*32;
	x[idx]=CenterX+addx;
	y[idx]=CenterY+addy;
  }
}

//2ボスビット
void Enemy::ptn2d(int& idx){
	int FirstPhase=180;  //最初に突っ込んでくる演出にかける時間
	int CenterX=320; //回転の中心X
	int CenterY=120;  //回転の中心Y
	int CircleMin=96;  //回転半径の最小
	int CircleMax=240;  //回転半径の最大
	double rad;
	if(phase[idx]<=FirstPhase){
		rad=mphase[idx]*RAD;
		/*最初ベジェ曲線で*/
		//始点
		int sx=(int)(CenterX-mycos(rad)*200);
		int sy=-64;
		//制御点
		int cx;
		if(PjSys::HardConst<4){cx=(int)(CenterX+mycos(rad)*400);}else{cx=(int)(CenterX+mycos(rad)*200);}
		int cy=760;
		//終点
		int ex=(int)(CenterX+mycos(rad)*CircleMin);
		int ey=(int)(CenterY+mysin(rad)*CircleMin);
		Get2DBezier(sx,sy,ex,ey,cx,cy,FirstPhase,phase[idx],&x[idx],&y[idx]);
		/*
	}else if(MogiMogiPhase>4){
		//ボス死亡
		rad=mphase[idx]*RAD;
		int ex=(int)(CenterX+cos(rad)*CircleMin);
		int ey=(int)(CenterY+sin(rad)*CircleMin);
		x[idx]+=(ex-x[idx])/90;
		y[idx]+=(ey-y[idx])/90;
		*/
	}else{
		/*通常動作*/
		if(PjSys::GameLevel==3){
			rad=mphase[idx]*RAD+(phase[idx]-FirstPhase)*RAD*0.25;
		}else{
			rad=mphase[idx]*RAD+(phase[idx]-FirstPhase)*RAD*0.5;
		}
		double maxhalf=CircleMax*0.5;
		double scl=CircleMin+maxhalf+mycos((phase[idx]-FirstPhase)*(0.004+(8-PjSys::HardConst)*0.001))*-maxhalf;
		double radb=(phase[idx])*RAD;
		double addx=mycos(radb*0.5)*32;
		double addy=mysin(radb)*32;
		x[idx]=CenterX+addx+mycos(rad)*scl;
		y[idx]=CenterY+addy+mysin(rad)*scl;
		if(x[idx]<-64){
			x[idx]=-64;
		}else if(x[idx]>640+64){
			x[idx]=640+64;
		}

		if(y[idx]<-64){
			y[idx]=-64;
		}else if(y[idx]>480+64){
			x[idx]=480+64;
		}
	}
}
void Enemy::ptn2e(int& idx){}


//3中ボス死んだ時
void Enemy::ptn2f(int& idx){
	math m;
	if (phase[idx] % 16 == 0){
		RegistExp(m.irand((int)x[idx] - 60, (int)x[idx] + 60), m.irand((int)y[idx] - 60, (int)y[idx] + 60), 1.0, m.irand(0, 15));
	}
	vx[idx] = 0 ;
	vy[idx] = 5;
	expansion[idx] *= 0.999f;
	z[idx] += 0.002f;
	/*if (bephase == 1){
		if (mphase[idx] == 0 && y[idx]>600){
			bephase = 2;
			y[idx] += 100;
			eb1[idx].init();
		}
	}
	*/
}

//3面中ボス
void Enemy::ptn3a(int& idx){
		//math m;
	if(phase[idx]<90){
		vy[idx]=mycos(RAD*phase[idx])*4;
		deg[idx]=static_cast<float>(RAD*phase[idx]/3);
	}else if(phase[idx]>60*55){
		vx[idx]=0;
		vy[idx]+=0.1;
	}else{
		vx[idx]=mycos(RAD*(phase[idx]-90)/2);
		vy[idx]=0;
		deg[idx]=(float)(mycos(RAD*(phase[idx]-90)/2)*30*RAD);

		if(mphase[idx]>0 && mphase[idx]<=30){
			vy[idx]+=mycos(RAD*mphase[idx]*6)*-4;
			//z[idx]-=(float)(cos(RAD*mphase[idx]*12)*-0.2);
			mphase[idx]++;
		}
	}

}
//3面ボス
void Enemy::ptn3b(int& idx){
		vx[idx] = mycos(RAD*(phase[idx] - 90) / 2)/4;
		vy[idx] = mysin(RAD*(phase[idx] - 90) ) / 8;

}