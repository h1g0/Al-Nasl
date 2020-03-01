#include "Common.h"
#include <boost/tokenizer.hpp>
/****************************************************************************************
_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

　　　　　　　　　　　　　　　　　ステージ管理実体

_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
*****************************************************************************************/

//=====================================================================================
//メニュー表示
//=====================================================================================
int StageManager::Menu(int* img, string_t str[], int Max){
	PjSys::Scr::BGWire=true;
	int FrmWait=20;
	int WndStatus = Window.GetStatus();
	if(WndStatus==-2 && ( GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_UP ) != 0 ){
		if(SelectKey[0]%FrmWait==1){
			PlaySoundMem(SndSelect,DX_PLAYTYPE_BACK);
				if(SelectedNo==0){
					SelectedNo=Max;
				}else{
					SelectedNo--;
				}
				mPhase=0;
		}
		SelectKey[0]++;
	}else{SelectKey[0]=0;}

	if(WndStatus==-2 && (GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_DOWN ) != 0 ){
		if(SelectKey[1]%FrmWait==1){
			PlaySoundMem(SndSelect,DX_PLAYTYPE_BACK);
				if(SelectedNo==Max){
					SelectedNo=0;
				}else{
					SelectedNo++;
				}
				mPhase=0;
		}
		SelectKey[1]++;
	}else{SelectKey[1]=0;}

	//キーコンフィグ画面では決定キー無効
	if(WndStatus==-2 && stage==0x93 && SelectedNo!=6){
		KeyConfig1();
	}else if(WndStatus==-2 && stage==0x95 && SelectedNo==1){
		KeyConfig2();
	}else{
		if((WndStatus==-2 && (GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::shot_p ) != 0) ||
			WndStatus ==1){
			if(SelectKey[2]==0){ //決定キーが押されたら
				//ボス戦へ飛ばす隠しコマンド
#ifdef DEBUG_COMMAND
				if(stage==0x81 && CheckHitKey(KEY_INPUT_B)){PjSys::cheat::Go2Boss=true;}else{PjSys::cheat::Go2Boss=false;}
#endif //DEBUG_COMMAND
				PlaySoundMem(SndOK,DX_PLAYTYPE_BACK);
				if(WndStatus==1){
					mSelected=0x11;
				}else{
					mSelected=SelectedNo;
				}
				mPhase=64;
			}
			SelectKey[2]=1;
		}else{SelectKey[2]=0;}

		if(WndStatus==-2 &&(GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::sub_p ) != 0 ){
			if(SelectKey[3]==0){
				PlaySoundMem(SndCancel,DX_PLAYTYPE_BACK);
				SelectKey[3]=1;
				mSelected = -2;
				mPhase=64;
			}
			SelectKey[3]=1;
		}else{SelectKey[3]=0;}

		//ヘルプ
		if(WndStatus==-2 &&(GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::bomb_p ) != 0 ){
			Window.SetString(str[SelectedNo],Window.DialogOK);
			Window.SetFlag();
		}

#ifdef DEBUG_COMMAND
		if(CheckHitKey(KEY_INPUT_LCONTROL)){ //始めるステージを選べる隠しコマンド
			if(CheckHitKey(KEY_INPUT_1)){PjSys::StartStage=0x10;}
			else if(CheckHitKey(KEY_INPUT_2)){PjSys::StartStage=0x20;}
			else if(CheckHitKey(KEY_INPUT_3)){PjSys::StartStage=0x30;}

		}
#endif //DEBUG_COMMAND
	}

	//bg.move();
	bg2.move();
	MV1SetRotationXYZ(bg2.hField,VGet((++bgphase*DX_PI_F/180.0f)/2,(bgphase*DX_PI_F/180.0f)/2,(bgphase*DX_PI_F/180.0f)/2));
	MV1SetPosition(bg2.hField,VGet(0.0f,0.0f,0.0f));
	MV1SetScale(bg2.hField,VGet(50.0f,50.0f,50.0f));
	MV1SetOpacityRate(bg2.hField, 0.5f ) ;
	MV1SetDifColorScale(bg2.hField, GetColorF( 0.1f, 1.0f, 0.1f, 0.3f ) ) ;
	MV1SetWireFrameDrawFlag(bg2.hField,true);

	MV1SetMaterialDrawBlendMode(bg2.hField,0,DX_BLENDMODE_ADD);
	MV1SetMaterialDrawBlendParam(bg2.hField,0,255);

	MV1DrawModel(bg2.hField);

	MV1SetMaterialDrawBlendMode(bg2.hField,0,DX_BLENDMODE_NOBLEND);
	MV1SetMaterialDrawBlendParam(bg2.hField,0,0);

	SetDrawBlendMode(DX_BLENDMODE_ADD,255);
	DrawRotaGraph(320,120,1.0,0,logo,true,false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	for(int i=0; i<=Max; i++){
		if(i==SelectedNo){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,127);
			if(mPhase<=32){
				DrawRectGraph(0 ,224+i*32 ,0,0,mPhase*20 ,32,BarImg,true ,false ) ;
				mPhase++;
			}else if(mPhase==96){
					SelectedNo=0;
					mPhase=0;
					SelectKey[2]=1;
					PjSys::Scr::BGWire=false;
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				if(mSelected == -2){
					return -2;
				}else if(mSelected ==0x11){
					return 0x11;
				}else{
					return i;
				} //キャンセルか否か
			}else if(mPhase>=64){
				SelectKey[2]=1;

				DrawRectGraph((mPhase-64)*20 ,224+i*32 ,(mPhase-64)*20,
								0,640-(mPhase-64)*20,32,BarImg,true ,false ) ;
				mPhase++;
			}else{
				DrawRotaGraph(320,240+i*32,1.0,0,BarImg,true,false);
			}

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
		if(i==SelectedNo){SetDrawBright(255,127,127);}
		DrawRotaGraph(320,240+i*32,1.0,0,img[i],true,false);
		SetDrawBright(255,255,255);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA	,127);
	DrawBox(0,450,640,480,GetColor(0,0,0),1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	//DrawString( 32 , 462 , str[SelectedNo], GetColor(32,32,32));
	static int fnt = CreateFontToHandle(NULL , 14 , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ;
	DrawStringToHandle( 10 , 460 , mOperateStr.c_str(), GetColor(255,255,255),fnt,GetColor(0,0,0));
	Window.Draw();
	if(WndStatus==0){return 0x10;}
	return -1;
}

//==================================================================
//ローディング
//==================================================================
void StageManager::Loading(int& img){
	int ix,iy;
	GetGraphSize( img , &ix ,&iy ) ;
	SetDrawBright(127,127,127);
	DrawGraph(640-ix,480-iy,img,true);
	SetDrawBright(255,255,255);
	phase++;
	//バー描画
	if(LoadElements>0 && phase>0){
		DrawBox(33,481-32,641-32,481-24,GetColor(96,96,96),0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
		int x2=(int)(phase*(640-32)/LoadElements);
		if(x2>=32){
			DrawBox(32,480-32,x2,480-24,GetColor(255-(int)(phase*255/LoadElements),0+(int)(phase*255/LoadElements),0),1);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawBox(32,480-32,640-32,480-24,GetColor(255,255,255),0);
		int alpha=(int)(127+(phase*128/LoadElements));
		SetDrawBlendMode(DX_BLENDMODE_ADD,alpha);
		DrawGraph(640-32-150,480-32-32,ImgLoadStr,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
}

//==================================================================
//メインステージ制御
//==================================================================

void StageManager::stgmove(){
	if(gPlayer.Pause(PauseImg)==1){return;}
	if(My::GOver==true){
		gPlayer.GameOver(GOimg);
		return;
	}

	//bg.move();
	bg2.move();
	//cloud.move();
	if(My::Move==true){
		gPlayer.Move();
		gPlayer.Bomb(InvImg);
	}
	My::x=gPlayer.mx;
	My::y=gPlayer.my;
	if(My::IsHit==true){gPlayer.Dead();}
	else if(My::GOver==false && My::Born==true){gPlayer.Born(GrPlane,BornEff);}
	else{gPlayer.Draw(GrPlane,&InvImg);}
	e1.Move();
	//if(My::GOver==true){gPlayer.GameOver(GOimg);}
	//e1.ShowExp();
	cloud.move();
	side.draw();
	phase++;
}

//==================================================================
//ステージ総合管理
//==================================================================

void StageManager::move(){
	int flg=0;
	if(stage==0x93 || stage==0x95){PjSys::CanExit=false;}else{PjSys::CanExit=true;} //キー設定中は終了阻止
	switch(stage){
		//最初のNotice
		case 0x0a:
			if(StgNotice()==1){phase=-1;stage=0x00;}
			break;
		//メインメニュー
		case 0:
			if(stg00()==1){phase=-1;stage=0x01;SelectedNo=0;}
			break;
		case 0x01:
			if(stg01()==1){phase=-1;}
			break;
		case 0x08:
			if(stg08()==1){phase=0;stage=PjSys::StartStage;}
			break;

		//レベル設定
		case 0x80:
			if(stg80()==1){phase=-1;stage=0x81;SelectedNo=1;}
			break;
		case 0x81:
			if(stg81()==1){phase=0;stage=0x08;}
			break;
		//設定メニュー
		case 0x90:
			if(stg90()==1){phase=0;stage=0x91;}
			break;
		case 0x91:
			if(stg91()==1){phase=0;stage=0x92;}
			break;
		//キーコンフィグ1
		case 0x92:
			if(stg92()==1){phase=0;stage=0x93;}
			break;
		case 0x93:
			if(stg93()==1){phase=0;stage=0x90;}
			break;
		//キーコンフィグ2
		case 0x94:
			if(stg94()==1){phase=0;stage=0x95;}
			break;
		case 0x95:
			if(stg95()==1){phase=0;stage=0x90;}
			break;
		//設定1
		case 0x96:
			if(stg96()==1){phase=0;stage=0x97;}
			break;
		case 0x97:
			if(stg97()==1){phase=0;stage=0x90;}
			break;
		//設定2
		case 0x98:
			if(stg98()==1){phase=0;stage=0x99;}
			break;
		case 0x99:
			if(stg99()==1){phase=0;stage=0x90;}
			break;
		//ランキング
		case 0xA0:
			if(stgA0()==1){phase=0;stage=0xA1;}
			break;
		case 0xA1:
			if(stgA1()==1){phase=0;stage=0x00;}
			break;

		//ステージ1
		case 0x10: //ロード
			if(stg10()==1){phase=-1;stage=0x18;}
			break;
		case 0x18: //出撃
			if(stg18()==1){phase=-1;stage=0x11;}
			break;

		case 0x11: //道中
			if(stg11()==1){phase=-1;stage=0x12;}
			break;
		case 0x12: //Warning
			if(stg12()==1){phase=-1;stage=0x13;}
			break;
		case 0x13: //ボス戦
			if(stg13()==1){phase=-1;stage=0x14;}
			break;
		case 0x14: //リザルト
			if(stg14()==1){phase=-1;stage=0x20;}
			break;
		//ステージ2(旧ステージ3)
		case 0x20: //ロード
			if(stg30()==1){phase=-1;stage=0x21;}
			break;
		case 0x21: //道中
			if(stg31()==1){
				phase=-1;
				stage=0x22;
				//UnloadSt2();
			}
			break;
		case 0x22: //Warning
			if(stg32()==1){phase=-1;stage=0x23;}
			break;
		case 0x23: //ボス戦
			if(stg33()==1){phase=-1;stage=0x24;}
			break;
		case 0x24: //リザルト
			if(stg14()==1){phase=-1;stage=0x30;}
			break;
		//ステージ3(旧ステージ2)
		case 0x30: //ロード
			if(stg20()==1){phase=-1;stage=0x31;}
			break;
		case 0x31: //道中
			if(stg21()==1){
				phase=-1;
				stage=0x32;
				//UnloadSt2();
			}
			break;
		case 0x32: //Warning
			if(stg22()==1){phase=-1;stage=0x33;}
			break;
		case 0x33: //ボス戦
			if(stg23()==1){phase=-1;stage=0x34;}
			break;
		case 0x34: //リザルト
			if(stg14()==1){phase=-1;stage=0x00;}
			break;

	}
}

void SmallWindow::AnalyzeStr(string_t &String){
	typedef boost::char_separator<char> char_separator;
	typedef boost::tokenizer<char_separator> tokenizer;
	char_separator sep("#", "", boost::keep_empty_tokens);
	tokenizer tokens(String, sep);
	Str.assign(tokens.begin(),tokens.end());
}

void SmallWindow::SwitchDialog(int DialogType){
	switch(DialogType){
		case DialogOK:
			DialogSelect.resize(1,"");
			DialogSelect[0]="< OK >";

			break;
		case DialogYesNo:
			DialogSelect.resize(2,"");
			DialogSelect[0]="< NO >";
			DialogSelect[1]="< YES >";
			break;
		default:
			DialogSelect.resize(1,"");
			DialogSelect[0]="< OK >";
			break;
	}
}

int SmallWindow::Draw(){
	if(flg==0){
		status=-2;
		return status;
	}
	static int p1[2]={0,0},p2[2]={0,0};
	static const int w_unit = (640-width)/(FadeFrm*2);
	static const int h_unit = (480-height)/(FadeFrm*2);

	if(flg<=FadeFrm){ //フェードイン
		if(flg ==1){
			PlaySoundMem(SndOpen,DX_PLAYTYPE_BACK);
		}
		p1[0]=w_unit*flg;
		p1[1]=240-h_unit*flg;
		p2[0]=640 - p1[0];
		p2[1]=480-p1[1];
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,192/*(int)(128/FadeFrm*flg)*/);
		DrawBox(p1[0],p1[1],p2[0],p2[1],GetColor(0,0,0),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawBox(p1[0],p1[1],p2[0],p2[1],GetColor(255,255,255),FALSE);
		flg++;
		status=-1;
		return status;
	}else if(flg > ShowingFrm && flg <=ShowingFrm + FadeFrm){ //フェードアウト
		int lflg = flg - ShowingFrm; //ローカルフラグ
		p1[0]=w_unit*(FadeFrm - lflg);
		p1[1]=240-h_unit*(FadeFrm - lflg);
		p2[0]=640 - p1[0];
		p2[1]=480-p1[1];
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,192/*-(int)(192/FadeFrm*lflg)*/);
		DrawBox(p1[0],p1[1],p2[0],p2[1],GetColor(0,0,0),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawBox(p1[0],p1[1],p2[0],p2[1],GetColor(255,255,255),FALSE);

		flg++;
		status=-1;
		return status;
	}else if(flg > ShowingFrm + FadeFrm){ //終了
		flg = 0;
		status=dialog_selected;
		return status;
	}else{ //通常描画
		//SetFontSize(FontSize);
		static int fnt = CreateFontToHandle( NULL , FontSize , 4 , DX_FONTTYPE_ANTIALIASING_EDGE ) ; //フォント

		SetDrawBlendMode(DX_BLENDMODE_ALPHA,192);
		DrawBox(p1[0],p1[1],p2[0],p2[1],GetColor(0,0,0),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawBox(p1[0],p1[1],p2[0],p2[1],GetColor(255,255,255),FALSE);

		//文字列描画
		for(unsigned int i=0;i<Str.size();i++){
			DrawStringToHandle(p1[0]+4,p1[1]+i*(FontSize+2)+4,Str.at(i).c_str(),GetColor(255,255,255),fnt);
		}

		//ダイアログの文字列描画
		for(unsigned int i=0;i<DialogSelect.size();i++){
			int col=(i==dialog_selected)?GetColor(255,127,127):GetColor(192,192,192);
			//横幅
			int wid = GetDrawStringWidthToHandle(DialogSelect[i].c_str(),DialogSelect[i].size(),fnt);
			int lx=(640 - wid)/2;
			int ly = p2[1]-32-(FontSize+2)*i;
			if(i==dialog_selected){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,192);
				//DrawBox(lx,ly,lx+wid,ly+FontSize+2,GetColor(0,0,0),TRUE);
				DrawModiGraph(lx,ly,lx+wid,ly,lx+wid,ly+FontSize+2,lx,ly+FontSize+2,ImgSelected,TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			}
			DrawStringToHandle(lx,ly,DialogSelect.at(i).c_str(),col,fnt);
		}

		//決定
		static int skey=0;

		if(( GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::shot_p ) != 0 ||
			( GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::bomb_p ) != 0 ||
			( GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PjSys::key::sub_p ) != 0 ){
			if( skey == 0 ){
				flg++;
				skey++;
				PlaySoundMem(SndClose,DX_PLAYTYPE_BACK);
			}
		}else{
			skey=0;
		}

		//↑
		static int ukey = 0;
		if(( GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_UP ) != 0){
			if(ukey == 0){
				if( dialog_selected>0){
					dialog_selected--;
				}else if(dialog_selected == 0){
					dialog_selected=DialogSelect.size()-1;
				}
			}
			ukey++;
			ukey%=30;
		}else{
			ukey=0;
		}

		//↓
		static int dkey = 0;
		if(( GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_DOWN ) != 0){
			if(dkey == 0){
				if( dialog_selected<(int)DialogSelect.size()-1){
					dialog_selected++;
				}else if(dialog_selected == DialogSelect.size()-1){
					dialog_selected=0;
				}
			}
			dkey++;
			dkey%=30;
		}else{
			dkey=0;
		}
		status=-1;
		return status;
	}
}