#include "Common.h"
/*#############################################################

						  メニュー等記述

##############################################################*/

/*================
System Message:
------------------
WARNING!
------------------
Prepare to Engage
against the
Mighty Enemy...
================*/
int StageManager::warn(){
//通常の描画==================
	//bg.move();
	bg2.move();
	cloud.move();
	My::Move=false;
	if(My::GOver==true){
		gPlayer.GameOver(GOimg);
	}else{
		if(My::Move==true){gPlayer.Move();gPlayer.Bomb(InvImg);}
		My::x=gPlayer.mx;
		My::y=gPlayer.my;
		if(My::IsHit==true){gPlayer.Dead();}
		else if(My::Born==true){gPlayer.Born(GrPlane,BornEff);}
		else{gPlayer.Draw(GrPlane,&InvImg);}
	}

	//e1.Move();
	side.draw();
//==========================================

//WARNING!!===================================
	if(phase<0){
		phase++;
	}else if(phase==0){
		//PlaySoundMem(SndAlarm,DX_PLAYTYPE_BACK);
			if(PlaySoundMem(SndAlarm,DX_PLAYTYPE_BACK)==-1){
				//何故か勝手にガーベージコレクトされるので、エラーが起きたら読み込み直し
				ErrorLogAdd("Alarm has been Reloaded.\n");
				SndAlarm=LoadSoundMem( "snd\\alarm.wav" ) ;
				ChangeVolumeSoundMem(Setting.General.SEVolume , SndAlarm );
				PlaySoundMem(SndAlarm,DX_PLAYTYPE_BACK,true);
			}
		PjSys::Scr::AddLog("- RADAR CONTACT -\0",My::NowStage,GetColor(255,127,127));
		phase++;
	}else if(phase==10){
		PjSys::Scr::AddLog("THE BIG ENEMY HAS\0",My::NowStage,GetColor(255,255,255));
		phase++;
	}else if(phase==20){
		PjSys::Scr::AddLog("BEEN ACQUIRED.\0",My::NowStage,GetColor(255,255,255));
		phase++;
	}else if(phase==30){
		PjSys::Scr::AddLog("RECOGNIZING...\0",My::NowStage,GetColor(255,255,255));
		phase++;
	}else if(phase<=40){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255*phase/40);
		DrawModiGraph(-280+phase*10, 240-285*phase/80, 920-phase*10, 240-285*phase/80,920-phase*10, 240+285*phase/80, -280+phase*10, 240+285*phase/80,warnimg,false);
		//DrawRectGraph(120,98,0,0,phase*10,285*phase/40,warnimg,false,false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		phase++;
	}else if(phase==41){
		SeekMovieToGraph(warnmov ,100 ) ;
		PlayMovieToGraph(warnmov);
		phase++;
	}else if(phase==42){
		DrawGraph(120,98,warnmov,false );
		//if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::shot_p ) != 0){PauseMovieToGraph(warnmov);}//ショットボタンが押されていたらスキップ
		if(GetMovieStateToGraph(warnmov)!=1){
			StopSoundMem(SndAlarm); //効果音停止。使わないなら削除でも良いかも？
			phase++;
		}
		if(Setting.General.English==false){
			//SetFontSize(16);
			//SetFontThickness(4);
			//ChangeFontType( DX_FONTTYPE_ANTIALIASING_EDGE) ;
			if(stage==0x12){
				DrawStringToHandle( 200 , 460 , "\"警告! 強大ナル敵トノ交戦ヲ覚悟セヨ…\"", GetColor(255,255,255),PjSys::font::caption,GetColor(0,0,0),0);
			}
		}
	}else if(phase<=82){
		int v=(int)(mycos(RAD*(90/40)*(phase-42))*Setting.General.BGMVolume);//BGMフェードアウト
		ChangeVolumeSoundMem(v , PjSys::bgm ) ;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-(255*(phase-42)/40));
		//DrawRectGraph(120+(phase-42)*10,98+285*(phase-42)/40,(phase-42)*10,285*(phase-42)/40,400,285,warnimg,false,false);
		DrawModiGraph(120-(phase-42)*10, 98+285*(phase-42)/80, 520+(phase-42)*10, 98+285*(phase-42)/80,520+(phase-42)*10, 98+285-285*(phase-42)/80, 120-(phase-42)*10, 98+285-285*(phase-42)/80,warnimg,false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		phase++;
	}else if(phase==83){
		DeleteSoundMem(PjSys::bgm) ;
		phase=0;
		My::Move=true;
		return 1;
	}else{phase++;}
	return 0;
}

/*
-------------------------
リザルト
--------------------------
Al-Nasl
Regular Combat Report

Strategy valuation score:
(y:180)
Tactics valuation score:
(y:300)
Your present score:
(y:420)
*/
int StageManager::result(){
	if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::shot_p ) != 0){
		if(SelectKey[0]==0){
			if(rphase>0 && rphase<60){
				rphase=60;
			}else if(rphase<120){
				rphase=120;
			}else if(rphase<180){
				rphase=180;
			}else if(rphase<240){
				rphase=240;
			}else if(rphase<480){
				rphase=480;
			}
			SelectKey[0]=1;
		}
	}else{
		SelectKey[0]=0;
	}

	if(rphase==1){
		ResultImg=LoadGraph("img\\result.bmp");
		ResultSound=LoadSoundMem("snd\\result.wav");
		ChangeVolumeSoundMem(Setting.General.SEVolume , ResultSound);
		//ChangeVolumeSoundMem(0 , ResultSound);
		PjSys::Scr::AddLog("CONFIRM THE LATEST",My::NowStage,GetColor(255,255,255));
		ResultScore[0]=My::Bomb*1000 + My::Left*5000;
		ResultScore[1]=BossRemainSec*500;
	}else if(rphase==10){
		PjSys::Scr::AddLog("REGULAR COMBAT REPORT",My::NowStage,GetColor(255,255,255));
	}

	if(rphase<60){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,phase*2);
		//DrawModiGraph(120,0, 520, 0, 520, rphase*8,120, rphase*8,ResultImg, TRUE );
		DrawRectGraph(120,0,0,0,400,rphase*8,ResultImg,TRUE,FALSE);
		int line=DerivationGraph(0,rphase*8,400,1,ResultImg);
		//DrawRectGraph(120,rphase*8,0,0,400,480-rphase*8,line,TRUE,FALSE);
		DrawModiGraph(120,rphase*8,520,rphase*8,520,480,120,480,line,TRUE);
		//printfDx("line: %d\n",line);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	//}else if(rphase==60){
	//	DeleteSoundMem(PjSys::bossbgm);
	}else if(rphase<420){
		//SetDrawBlendMode(DX_BLENDMODE_ADD,128);
		SetDrawMode(1);
		DrawGraph(120,0,ResultImg,TRUE);
		SetDrawMode(0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

		PjSys::NumDraw(PjSys::MainNum,My::Score,420,420,16); //現在の得点

		if(rphase==120){
			//My::AddScore(My::NowStage*10000); //戦略評価点
			PlaySoundMem(ResultSound,DX_PLAYTYPE_BACK);
		}
		if(rphase>120){
			PjSys::NumDraw(PjSys::MainNum,ResultScore[0],420,180,16); //戦略評価点
		}
		if(rphase==180){
			//My::AddScore((8-PjSys::HardConst)*2000); //難易度ボーナス
			PlaySoundMem(ResultSound,DX_PLAYTYPE_BACK);
		}
		if(rphase>180){
			PjSys::NumDraw(PjSys::MainNum,ResultScore[1],420,300,16); //戦略評価点
		}
		if(rphase==240){
			PlaySoundMem(ResultSound,DX_PLAYTYPE_BACK);
			My::AddScore(ResultScore[0]);
			My::AddScore(ResultScore[1]);
			ResultScore[0]=0;
			ResultScore[1]=0;
		}
	}else if(rphase==420){
		AppLogAdd("*** Accomplished [Stage 0%d]. Your score was %d pts. ***\n",My::NowStage,My::Score);
		//PlaySoundMem(ResultSound,DX_PLAYTYPE_BACK);
	}else if(rphase>420){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(480-phase)*2);
		int lphase=(rphase-420)*8;
		//DrawModiGraph(120,(rphase-420)*8, 520, (rphase-420)*8, 520, 480,120, 480,ResultImg, false );

		DrawRectGraph(120,lphase,0,lphase,400,480-lphase,ResultImg,TRUE,FALSE);
		int line=DerivationGraph(0,480-lphase,400,1,ResultImg);
		DrawModiGraph(120,0,520,0,520,lphase,120,lphase,line,TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		ChangeVolumeSoundMem((int)(Setting.General.BGMVolume*mycos((rphase-420)*1.5*RAD)),PjSys::bossbgm);
	}
	if(rphase==480){
		DeleteSoundMem(PjSys::bossbgm);
		return 1;
	}
	rphase++;
	return 0;
}

int StageManager::ShowStageTitle(int phase){
	if(phase>=0 && phase<60){ //ステージ表示1
		//My::Move=false;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(phase-10)*2);
		int line=DerivationGraph( 0,(int)(200/60*(phase-10)),400, 1, stgimg ) ;
		DrawModiGraph( 120, 140, 520, 140,520, 140+(int)(200-(200/60*(phase-10))), 120, 140+(int)(200-(200/60*(phase-10))),line, true );
		DrawRectGraph( 120, 140+(int)(200-(200/60*(phase-10))),0,(int)(200-(200/60*(phase-10))), 400, (int)(200/60*(phase-10)),stgimg, true,false ) ;
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}else if(phase>=60 && phase<360){ //ステージ表示2
		//My::Move=false;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
		DrawGraph(120,140, stgimg,true) ;
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}else if(phase>=360 && phase<420){ //ステージ表示3
		//My::Move=false;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120-(phase-370)*2);
		int line=DerivationGraph( 0,(int)(200-(200/60*(phase-370))),400, 1, stgimg ) ;
		DrawModiGraph( 120, 340-(int)(200/60*(phase-370)), 520, 340-(int)(200/60*(phase-370)),520, 340, 120, 340,line, true );
		DrawRectGraph( 120, 140,0,0, 400, (int)(200-(200/60*(phase-370))),stgimg, true,false ) ;
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}else if(phase==420){
		return 1;
	}
	return 0;
}