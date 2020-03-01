#include "Common.h"
/*#############################################################

						   �G�e����

##############################################################*/
/*==============================================================
�G�e�N���X
===============================================================*/

EBullet::EBullet(){
	Init();
}

void EBullet::Init(){
	flg=0;
	deg=0;
	x=0;
	y=0;
	vx=0;
	vy=0;
	deg=0;
	scl=0;
	snpdeg=0;
	snipe=0;
	queue=-1;
	imgidx=0;
	imgc=0;
	dead=0;
	parent_dead=0;
	visible=false;
	disapear=false;
	buzzfrm=0;
}
/*
void EBullet::def(int& bimg,double& defx, double& defy, double& defvx, double& defvy, int& defqueue,double& defdeg){
	px=&defx;
	py=&defy;
	vx=defvx;
	vy=defvy;
	queue=defqueue;
	flg=1;
	imgidx=0;
	img=&bimg;
	phase=0;
	imgc=0;
	deg=defdeg;
	snipe=0;
}
*/

//�G�e�ʏ��`�B����: �G�e�摜�E�G�e�𔭎˂�����W�A�i�s�ʁA�L���[
void EBullet::def(int& bimg,double& defx, double& defy, double& defvx, double& defvy, int& defqueue){
	px=&defx;
	py=&defy;
	vx=defvx;
	vy=defvy;
	queue=defqueue;
	flg=1;
	imgidx=0;
	img=&bimg;
	phase=0;
	imgc=0;
	math m;
	deg=m.vec2rad(vx,vy);
	snipe=0;
}

//�G�e�i�s�ʍĒ�`�B����: �i�s��
void EBullet::vectordef(double& defvx, double& defvy){
	math m;
	vx=defvx;
	vy=defvy;
	deg=m.vec2rad(vx,vy);
}
/*
void EBullet::vectordef(double& defvx, double& defvy,double& defdeg){
	vx=defvx;
	vy=defvy;
	deg=defdeg;
}
*/

void EBullet::snipedef(int& bimg,double& defx, double& defy, double scalar, double defdeg, int& defqueue){
	px=&defx;
	py=&defy;
	queue=defqueue;
	flg=1;
	imgidx=0;
	img=&bimg;
	phase=0;
	imgc=0;
	snpdeg=defdeg;
	snipe=1;
	scl=scalar;
}

void EBullet::sniperedef(double scalar, double defdeg){
	snpdeg=defdeg;
	snipe=1;
	scl=scalar;
}

//������
int EBullet::Move(){
	bool buzz=false;

	if(flg==1){
		if(queue==0){ //�L���[��0�ȉ�(=�e�����݂���)���H
			if(phase==0){
				math m;
				//��ʊO��������t���O�������ďI��
				if(*px>=120 && *px<=520 && *py>=0 && *py<=480){
					x=*px;
					y=*py;
					flg=1;
				 }else{
					x=-1;
					y=-1;
					vx=0;
					vy=0;
					flg=0;
					return 0;
				}

				//�ˌ���
				if(CheckSoundMem(Enm::SndShot)==0){
					PlaySoundMem(Enm::SndShot,DX_PLAYTYPE_BACK,true);
				}else if(CheckSoundMem(Enm::SndShot)==-1){
					#ifdef RELOADSOUND
						ErrorLogAdd("Enm::SndShot has been Reloaded.\n");
						Enm::SndShot=LoadSoundMem( "snd\\enmshot.wav" ) ;
						ChangeVolumeSoundMem(Setting.General.SEVolume ,Enm::SndShot );
						PlaySoundMem(Enm::SndShot,DX_PLAYTYPE_BACK,true);
					#endif
				}
				DrawGraph((int)x+PjSys::Scr::MoveX-16 ,(int) y+PjSys::Scr::MoveY-16, Enm::FireFlare , TRUE);
				//------

				disapear=false;
				if(snipe==1){//�_���e�t���O�������Ă���
					snipe=0;
					vx=m.getcos(x,y,My::x,My::y);
					vy=m.getsin(x,y,My::x,My::y);
					if(snpdeg!=0){ //�p�x���t������Ă�����A�x�N�g�����I�[�o�[���C�h
						double srad;
						srad=PI-(m.vec2rad(vx,vy)+m.ToRadian(snpdeg));
						vx=mysin(srad);
						vy=mycos(srad);
					}
					deg=m.vec2rad(vx,vy);
					vx*=scl;
					vy*=scl;
				}
			}else{
				//�{���������Ă��邩�H
				if(dead == 0 && (My::BombFrame>0 || PjSys::cheat::Peacist==true)){
					if(My::IsAutoBomb==false && PjSys::cheat::Peacist==false){ //�ʏ�{����������{�[�i�X�_
						if(My::BombDeletedBullet++<=256){
							My::BombDeletedBullet;
							int score=My::BombDeletedBullet*4;
							My::AddScore(score);
						}
						My::AddSubEnergy(1);
					}
					dead=1;
				}

				if(snipe==1 && x>=120 && x<=520 && y>=0 && y<=480){//�_���e�t���O�������Ă���
					snipe=0;
					math m;
					vx=m.getcos(x,y,My::x,My::y);
					vy=m.getsin(x,y,My::x,My::y);
					if(snpdeg!=0){ //�p�x���t������Ă�����A�x�N�g�����I�[�o�[���C�h
						double srad;
						srad=PI-(m.vec2rad(vx,vy)+m.ToRadian(snpdeg));
						vx=mysin(srad);
						vy=mycos(srad);
					}
					deg=m.vec2rad(vx,vy);
					vx*=scl;
					vy*=scl;
				}

				double Scr=1.0;
				//�ʃ��[�h
				if(PjSys::IrodoriMode){
					Scr=IRODORI_RATE;
					Scr=IRODORI_RATE;
				}
				if(PjSys::AccelMode){
					vx*=ACCELERATOR_RATE;
					vy*=ACCELERATOR_RATE;
				}
				//Insane��2�{�e���o��(=1�t���[����EBCmd::Move()��2���)�̂ł��̑΍�
				if(PjSys::GameLevel==0){
					Scr=0.5;
				}

				if(Enm::Refuge::AnyAvaliable==true){//���G�n�т����݂��邩�H
					math m;
					for(int i=0;i<REFUGE_MAX;i++){
						if(Enm::Refuge::flg[i]==true &&
						   m.hitcheck(x,y,Enm::BltRegion,Enm::BltRegion,
									  Enm::Refuge::x[i],Enm::Refuge::y[i],
									  Enm::Refuge::width[i],Enm::Refuge::height[i])==1){
							dead=1;
							vx=0;
							vy=0;
						}
					}
				}

				if(My::DefFrame>SUBINVFRAME && dead==0){ //�f�B�t�F���_�[����
					math m;
					//PjSys::Scr::BGWire=true;
					double dist=m.GetDist2(x,y,My::x,My::y);
					if(dist<=64*64){
						//if(My::SubLevel==SUB_LEVEL){
						//���t���N�g��
						//My::AddScore(10);
						My::Laser::Regist();

						dead=1;
						vx=0;
						vy=0;
					}else{
						x+= vx*Scr;
						y+= vy*Scr;
					}

				//�����I�ɒx������
				}else if(gPlayer.GetIsSlow()==true && dead==0 && My::NowInv==false){
						math m;

						double dist=m.GetDist2(x,y,My::x,My::y);
						if(dist<=16*16 && m.GetDist2(x+vx,y+vy,My::x,My::y)<dist*dist){
							SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
							//DrawCircle((int)My::x,(int)My::y,16,GetColor(0,0,0),1);
							DrawLine((int)My::x,0,(int)My::x,(int)My::y-16,GetColor(128,128,0));
							DrawLine((int)My::x,(int)My::y+16,(int)My::x,480,GetColor(128,128,0));
							DrawLine(0,(int)My::y,(int)My::x-16,(int)My::y,GetColor(128,128,0));
							DrawLine((int)My::x+16,(int)My::y,640,(int)My::y,GetColor(128,128,0));
							DrawCircle((int)My::x,(int)My::y,16,GetColor(255,255,0),0);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
							x+=vx*Scr*0.17;
							y+=vy*Scr*0.17;
							if(My::NowBuzz<BUZZMAX){My::NowBuzz++;}
							//My::AddScore(3);
							//PjSys::Scr::BGWire=true;
						}else{
							x+= vx*Scr;
							y+= vy*Scr;
							//PjSys::Scr::BGWire=false;
						}
				}else{
					x+= vx*Scr;
					y+= vy*Scr;
					//PjSys::Scr::BGWire=false;
				}
			}

			phase++;
			math m;
			if(dead==0 && m.GetDist2(x,y,My::x,My::y)<=My::BuzzRegion*My::BuzzRegion){ //�o�Y���Ă邩�H
				if(My::NowBuzz<BUZZMAX){My::NowBuzz++;}
				buzz=true;
				if(CheckSoundMem(Enm::SndBuzz)==0){
					PlaySoundMem(Enm::SndBuzz,DX_PLAYTYPE_BACK,true);
				}else if(CheckSoundMem(Enm::SndBuzz)==-1){
					#ifdef RELOADSOUND
					ErrorLogAdd("Enm::SndBuzz has been Reloaded.\n");
					Enm::SndBuzz=LoadSoundMem( "snd\\buzz.wav" ) ;
					ChangeVolumeSoundMem(Setting.General.SEVolume ,Enm::SndBuzz );
					PlaySoundMem(Enm::SndBuzz,DX_PLAYTYPE_BACK,true);
					#endif
				} //�o�Y��
			}

			if(My::NowInv==false){ //���G����Ȃ��H
				if(dead==0 && m.hitcheck(x,y,Enm::BltRegion,Enm::BltRegion,My::x,My::y,My::Region,My::Region)==1){ //�e���������Ă���
					My::IsHitFrm=true;
					//Init();
					//return 1;
				}
			}
			/*
			if(My::IsHit==true){ //��яo���Ă���e������
				x+=1000;
				y+=1000;
			}*/

			if(dead>=1){ //�e������ł�����
				if(dead>30){
					x=-1000;
					y=-1000;
					vx=0;
					vy=0;
					//flg=0;
					//dead=0;
				}else{dead++;}
			}

			if(x<0 || x>640 ||y<0 || y>480 ){ //��яo������
				//Init();
				disapear=true;
				return -1;
			}else if(dead<=30){
				//�A�j���[�V����
				if(++imgc==10){
					imgc=0;
					//imgv=1;
					imgidx++;
					if(imgidx==4){imgidx=0;}
				}

				//�`��
				if(Setting.Optional.DrawTrack){ //�O�Օ\��
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,64) ;
					DrawLine((int)(x-vx*2+PjSys::Scr::MoveX),(int)(y-vy*2+PjSys::Scr::MoveY) ,(int)(x-vx*20+PjSys::Scr::MoveX),(int)(y-vy*20+PjSys::Scr::MoveY) ,GetColor(128,128,128) ) ;
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0) ;
				}
				if(Setting.Optional.DrawProspect){ //�\���\��
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,32) ;
					DrawLine((int)(x+vx*4+PjSys::Scr::MoveX),(int) (y+vy*4+PjSys::Scr::MoveY) ,(int)(x+vx*60+PjSys::Scr::MoveX),(int)(y+vy*60+PjSys::Scr::MoveY) ,GetColor(255,255,255) ) ;
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0) ;
				}
				SetDrawMode( 1 ) ;
				if(dead==0){
					DrawRotaGraph((int)x+PjSys::Scr::MoveX ,(int) y+PjSys::Scr::MoveY  , 1.0f , deg , img[imgidx] , TRUE);
				}else{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,127);
					DrawRotaGraph((int)x+PjSys::Scr::MoveX ,(int) y+PjSys::Scr::MoveY  , 1.0f , deg , Enm::ImgBltItem[(dead%2==0)?(int)(dead/2):(int)((dead-1)/2)] , TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				}
				SetDrawMode( 0 ) ;
				PjSys::DrawGuide((int)x-Enm::BltRegion/2 , (int)y-Enm::BltRegion/2 , (int)x+Enm::BltRegion/2 ,(int)y+Enm::BltRegion/2 );
				if(buzz){
					//DrawRotaGraph((int)x,(int)y,1.0f,0,My::imgRegion,true);
					buzz=false;
				}
				visible=true;
				return 1;
			}else{
				disapear=true;
				return -1;
			}
		}else{
			if(dead==0 && parent_dead==0){
				queue--;
				return 0;
			}else{
				//Init();
			}
		}
	}else{
		return -2;
	}
	return 0; //�Ō�܂œ��B���Ȃ�����
}

/*==============================================================
�G�e���w���N���X
===============================================================*/
//�R���X�g���N�^
EBCmd::EBCmd(){
	init();
}

//������
void EBCmd::init(){
	int i=0;
	while(i<EBCAP){
		eb[i].Init();
		i++;
	}
}

//�摜�Z�b�g
void EBCmd::setimg(int* ebimg){
	img=ebimg;
}

//�G�e������
void EBCmd::Create(int cap, int type, double& defx, double& defy){
	t=type;
	//Insane�͒e��2�{
	if(PjSys::GameLevel==0 && cap*2<EBCAP){
		c=cap*2;
	}else{
		c=cap;
	}
	cp=0;
	deg=0;
	k=1;
	px=&defx;
	py=&defy;
	l=0;
	dead=0;
	parent_dead=0;
	for(int i=0;i<c;i++){
		eb[i].Init();
	}
}

int EBCmd::Move(){ //������
	int loop=0; //���T�ځH
	int f=1;//�G�e���S�ď����Ă��邩�̃t���O
	if(PjSys::GameLevel==0){
		loop=2; //Insane
	}else{
		loop=1;
	}
	for(int j=0;j<loop;j++){ //2���ڂ�������2��
		for(int i=0;i<c;i++){ //���[�v��
			if(dead==1){ //�e������ł�����
				eb[i].dead=1;
				eb[i].img = Enm::ImgBltItem;
			}

			if(parent_dead==1){ //�G������ł�����
				eb[i].parent_dead=1;
			}
			//TODO: ����p�^�[���̕���͐V�����֐��ɂ����������₷���Ǝv��
			//����p�^�[���̕���
			switch(t){
			case 0x100:
				ptn100(i);
				break;
			case 0x101:
				ptn101(i);
				break;
			case 0x102:
				ptn102(i);
				break;
			case 0x103:
				ptn103(i);
				break;
			case 0x104:
				ptn104(i);
				break;
			case 0x105:
				ptn105(i);
				break;
			case 0x106:
				ptn106(i);
				break;
			case 0x107:
				ptn107(i);
				break;
			case 0x108:
				ptn108(i);
				break;
			case 0x109:
				ptn109(i);
				break;
			case 0x10a:
				ptn10a(i);
				break;
			case 0x10b:
				ptn10b(i);
				break;
			case 0x10c:
				ptn10c(i);
				break;
			case 0x10d:
				ptn10d(i);
				break;
			case 0x10e:
				ptn10e(i);
				break;
			case 0x10f:
				ptn10f(i);
				break;
//�{�X�e��
			case 0x1a1:
				ptn1a1(i);
				break;
			case 0x1a2:
				ptn1a2(i);
				break;
			case 0x1a3:
				ptn1a3(i);
				break;
			case 0x1a4:
				ptn1a4(i);
				break;
			case 0x1a5:
				ptn1a5(i);
				break;
			case 0x1a6:
				ptn1a6(i);
				break;
			case 0x1a7:
				ptn1a7(i);
				break;
			case 0x1a8:
				ptn1a8(i);
				break;
			case 0x1a9:
				ptn1a9(i);
				break;
//2��
			case 0x200:
				ptn200(i);
				break;
			case 0x201:
				ptn201(i);
				break;
			case 0x202:
				ptn202(i);
				break;
			case 0x203:
				ptn203(i);
				break;
			case 0x204:
				ptn204(i);
				break;
			case 0x205:
				ptn205(i);
				break;
			case 0x206:
				ptn206(i);
				break;
			case 0x207:
				ptn207(i);
				break;
			case 0x208:
				ptn208(i);
				break;
			case 0x209:
				ptn209(i);
				break;
			case 0x20a:
				ptn20a(i);
				break;
			case 0x20b:
				ptn20b(i);
				break;
			case 0x20c:
				ptn20c(i);
				break;
			case 0x20d:
				ptn20d(i);
				break;
			case 0x20e:
				ptn20e(i);
				break;
			case 0x20f:
				ptn20f(i);
				break;
		//3��
			case 0x300:
				ptn300(i);
				break;
			case 0x301:
				ptn301(i);
				break;
			case 0x302:
				ptn302(i);
				break;
			case 0x303:
				ptn303(i);
				break;
			case 0x304:
				ptn304(i);
				break;
			case 0x305:
				ptn305(i);
				break;
			case 0x306:
				ptn306(i);
				break;
			case 0x307:
				ptn307(i);
				break;
			case 0x308:
				ptn308(i);
				break;
			case 0x309:
				ptn309(i);
				break;

			case 0x30a:
				ptn30a(i);
				break;
			case 0x30b:
				ptn30b(i);
				break;
			case 0x30c:
				ptn30c(i);
				break;
			case 0x30d:
				ptn30d(i);
				break;
			case 0x30e:
				ptn30e(i);
				break;
			case 0x30f:
				ptn30f(i);
				break;

			case 0x3a0:
				ptn3a0(i);
				break;
			case 0x3a1:
				ptn3a1(i);
				break;
			case 0x3a2:
				ptn3a2(i);
				break;
			case 0x3a3:
				ptn3a3(i);
				break;
			case 0x3a4:
				ptn3a4(i);
				break;
			case 0x3a5:
				ptn3a5(i);
				break;
			case 0x3a6:
				ptn3a6(i);
				break;
			case 0x3a7:
				ptn3a7(i);
				break;
			case 0x3a8:
				ptn3a8(i);
				break;
			case 0x3a9:
				ptn3a9(i);
				break;

			}

			eb[i].Move();
			//�G�e�������Ă��邩�H
			if(eb[i].disapear && f==1){
				f=1;
			}else{
				f=0;
			}
		}
	}
	if(f==1){
		return 1;
	}else{
		return 0;
	}
}