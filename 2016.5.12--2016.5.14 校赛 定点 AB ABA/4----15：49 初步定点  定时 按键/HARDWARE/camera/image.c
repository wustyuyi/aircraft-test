#include "image.h"

#define _min(x,y) (x>y?y:x)
#define Threshold   100
#define _abs(x) ((x)>=0?(x):-(x))




IMAGE_INF img = 
{
     120,
     160,
      10,
      0,
      0,
			0,
};


void GetCenter(void)
{
	uint16_t m,n,a,b,c,w;
	w=_min(IMG_W,IMG_H);
	if(img.CerPtx>0 && img.CerPtx<IMG_W && img.CerPty>0 && img.CerPty<IMG_H)// && IMAGE[*py][*px]<threshold)
	{
		img.CerR=CheckCenterR(&img.CerPtx,&img.CerPty,img.CerPtx,img.CerPty,240);
		if(img.CerR)
			return;
	}
	for(a=2; w/a>=4; a*=2)
	{
		for(b=1; b<a; b+=2)
		{
			for(c=1; c<a; c+=2)
			{
				m=IMG_W*b/a;
				n=IMG_H*c/a;
				img.CerR=CheckCenterR(&img.CerPtx,&img.CerPty,m,n,240);
				if(img.CerR)
					return;
			}
		}
	}
	img.CerPtx=0;img.CerPty=0;
	return;
}

uint16_t CheckCenterR(uint16_t *px,uint16_t *py,uint16_t m,uint16_t n,uint16_t maxR)
{
	uint8_t flag;
	short cl,cr,ct,cb;
	short lt,rt,rb,lb;
	int rr[8],r1;
	int dt;
	if(IMAGE[n][m]>Threshold)
		return 0;
	flag=0;
	for(cl=m; IMAGE[n][cl]<Threshold; cl--)
	{
		if(m-cl>maxR || cl<=0)
		{
			flag|=0x01;
			break;
		}
	}
	for(cr=m; IMAGE[n][cr]<Threshold; cr++)
	{
		if(cr-m>maxR || cr>=IMG_W-1)
		{
			flag|=0x02;
			break;
		}
	}
	for(ct=n; IMAGE[ct][m]<Threshold; ct--)
	{
		if(n-ct>maxR || ct<=0)
		{
			flag|=0x04;
			break;
		}
	}
	for(cb=n; IMAGE[cb][m]<Threshold; cb++)
	{
		if(cb-n>maxR || cb>=IMG_H-1)
		{
			flag|=0x08;
			break;
		}
	}
	
	if(flag==0)
	{
		dt=n*(n-ct-cb)+cb*ct-m*(m-cl-cr)-cl*cr;
		if(_abs(dt)>400)
			return 0;
		m=(cr+cl)/2;
		n=(ct+cb)/2;
		flag=0;
		for(cl=m; IMAGE[n][cl]<Threshold; cl--)
		{
			if(cl<=0 || m-cl>maxR)
			{
				flag++;
				cl=m;
				break;
			}
		}
		for(cr=m; IMAGE[n][cr]<Threshold; cr++)
		{
			if(cr>=IMG_W-1 || cr-m>maxR)
			{
				flag++;
				cr=m;
				break;
			}
		}
		for(ct=n; IMAGE[ct][m]<Threshold; ct--)
		{
			if(ct<=0 || n-ct>maxR)
			{
				flag++;
				ct=n;
				break;
			}
		}
		for(cb=n; IMAGE[cb][m]<Threshold && cb<IMG_H; cb++)
		{
			if(cb>=IMG_H-1 || cb-n>maxR)
			{
				flag++;
				cb=n;
				break;
			}
		}
		for(lt=0; IMAGE[n-lt][m-lt]<Threshold; lt++)
		{
			if(n-lt<=0 || m-lt<=0 || lt>=maxR)
			{
				flag++;
				lt=0;
				break;
			}
		}
		for(rt=0; IMAGE[n-rt][m+rt]<Threshold; rt++)
		{
			if(n-rt<=0 || m+rt>=IMG_W-1 || rt>=maxR)
			{
				flag++;
				rt=0;
				break;
			}
		}
		for(rb=0; IMAGE[n+rb][m+rb]<Threshold; rb++)
		{
			if(n+rb>=IMG_H-1 || m+rb>=IMG_W-1 || rb>=maxR)
			{
				flag++;
				rb=0;
				break;
			}
		}
		for(lb=0; IMAGE[n+lb][m-lb]<Threshold && n+lb<IMG_H && m-lb>0; lb++)
		{
			if(n+lb>=IMG_H-1 || m-lb<=0 || lb>=maxR)
			{
				flag++;
				lb=0;
				break;
			}
		}
		if(flag>2)
			return 0;
		rr[0]=m-cl;rr[1]=cr-m;rr[2]=n-ct;rr[3]=cb-n;
		rr[4]=lt*1.414f;rr[5]=rt*1.414f;rr[6]=rb*1.414f;rr[7]=lb*1.141f;
		sort(rr,8);
		if(((rr[4]-rr[0])<(rr[3]>>2)+5)||((rr[5]-rr[1])<(rr[3]>>2)+5)||((rr[6]-rr[2])<(rr[4]>>2)+5)||((rr[7] - rr[3])<(rr[5] >> 2) + 5))
		{
			r1=(rr[4]+rr[3])/2;
			*px=m;
			*py=n;
			return r1;
		}
	}
	return 0;
}


//排序算法
void sort(int *a, uint16_t n) 
{
    int temp;
		uint16_t i,j;
    for(i=1;i<n;i++) 
    { 
        for(j=0;j<n-i;j++) 
        { 
            if(a[j]>a[j+1]) //???????? 
            { 
                temp=a[j]; a[j]=a[j+1]; a[j+1]=temp; 
            } 
        } 
    } 
}

uint8_t DirF=0;

//判断两个点是否与原点共线
uint8_t isOnLine(int dx1,int dy1,int dx2,int dy2)
{
	int dis;
	dis=(dx1*dy2-dx2*dy1)/sqrt(dx1*dx1+dy1*dy1);
	return _abs(dis)<5;
}


uint8_t CheckLine(uint16_t x, uint16_t y, LINE_S *pLine, uint16_t range,uint8_t dir)
{
	uint16_t cl, cr, ct, cb;
	uint16_t lenx, leny;
	uint8_t flag = 0;
	if (IMAGE[y][x]>Threshold)
		return 0;
	for (cl = x; IMAGE[y][cl] < Threshold; cl--)
	{
		if (cl <= 0 || cl + range <= x)
		{
			flag |= 0x01;
			break;
		}
	}
	for (cr = x; IMAGE[y][cr]<Threshold; cr++)
	{
		if (cr >= IMG_W || cr>=x + range)
		{
			flag |= 0x02;
			break;
		}
	}
	for (ct = y; IMAGE[ct][x] < Threshold; ct--)
	{
		if (ct <= 0 || ct + range <= y)
		{
			flag |= 0x04;
			break;
		}
	}
	for (cb = y; cb < IMG_H && cb < y + range && IMAGE[cb][x] < Threshold; cb++)
	{
		if (cb >= IMG_H || cb >= y + range)
		{
			flag |= 0x08;
			break;
		}
	}
	lenx = (flag & 0x03) ? IMG_W : (cr - cl);
	leny = (flag & 0x0c) ? IMG_H : (cb - ct);
	if (lenx < leny && lenx < 30 && (dir&0x01))
	{
		short tx = x, ty = y - 2, bx = x, by = y + 2;
		short tcx = x, tcy = y - 1, bcx = x, bcy = y + 1;
		x = (cr + cl) >> 1;
		flag = 0;
		for (cl = tcx; IMAGE[tcy][cl] < Threshold; cl--)
		{
			if (cl <= 0 || cl <= tcx - lenx)
			{
				flag |= 0x01;
				break;
			}
		}
		for (cr = tcx; cr < IMG_W && cr < tcx + lenx && IMAGE[tcy][cr] < Threshold; cr++)
		{
			if (cr >= IMG_W || cr >= tcx + lenx)
			{
				flag |= 0x02;
				break;
			}
		}
		if (flag == 0 && _abs(lenx - cr + cl)<5)
		{
			tcx = (cr + cl) >> 1;
			while (1)
			{
				tx = x - (x - tcx) * 2;
				ty = y - (y - tcy) * 2;
				if (tx<2)
				{
					tx = 1;
					ty = (tcy - y)*(tx - x) / (tcx - x) + y;
				}
				if (tx>IMG_W - 2)
				{
					tx = IMG_W - 1;
					ty = (tcy - y)*(tx - x) / (tcx - x) + y;
				}
				if (ty<2)
				{
					ty = 1;
					tx = (tcx - x)*(ty - y) / (tcy - y) + x;
				}
				if (tx == 1 || tx == IMG_W - 1 || ty == 1)
					break;
				if (IMAGE[ty][tx]<Threshold)
				{
					flag = 0;
					for (cl = tx; IMAGE[ty][cl] < Threshold; cl--)
					{
						if (cl <= 0 || cl <= tx - lenx)
						{
							flag |= 0x01;
							break;
						}
					}
					for (cr = tx; IMAGE[ty][cr] < Threshold; cr++)
					{
						if (cr >= IMG_W || cr >= tx + lenx)
						{
							flag |= 0x02;
							break;
						}
					}
					if (flag)
						break;
					tx = (cr + cl) >> 1;
					if (_abs(lenx - cr + cl)<5 && isOnLine(tcx - x, tcy - y, tx - x, ty - y))
					{
						tcx = tx; tcy = ty;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			while (tcy > ty + 1)
			{
				short tccy = (ty + tcy) / 2;
				short tccx = (tcx - x)*(tccy - y) / (tcy - y) + x;
				if (IMAGE[tccy][tccx]<Threshold)
				{
					flag = 0;
					for (cl = tccx; IMAGE[tccy][cl] < Threshold; cl--)
					{
						if (cl <= 0 || cl <= tccx - lenx)
						{
							flag |= 0x01;
							break;
						}
					}
					for (cr = tccx; IMAGE[tccy][cr] < Threshold; cr++)
					{
						if (cr >= IMG_W || cr >= tccx + lenx)
						{
							flag |= 0x02;
							break;
						}
					}
					if (flag)
					{
						tx = tccx; ty = tccy;
					}
					else if (_abs(lenx - cr + cl) < 5)
					{
						tccx = (cl + cr) >> 1;
						if (isOnLine(tcx - x, tcy - y, tccx - x, tccy - y))
						{
							tcx = tccx; tcy = tccy;
						}
						else
						{
							tx = tccx; ty = tccy;
						}
					}
					else
					{
						tx = tccx; ty = tccy;
					}
				}
				else
				{
					tx = tccx; ty = tccy;
				}
			}
			tx = tcx; ty = tcy;
		}
		else return 0;

		flag = 0;
		for (cl = bcx; IMAGE[bcy][cl] < Threshold; cl--)
		{
			if (cl <= 0 || cl <= bcx - lenx)
			{
				flag |= 0x01;
				break;
			}
		}
		for (cr = bcx; cr < IMG_W && cr < bcx + lenx && IMAGE[bcy][cr] < Threshold; cr++)
		{
			if (cr >= IMG_W && cr >= bcx + lenx)
			{
				flag |= 0x02;
				break;
			}
		}
		if (flag==0 && _abs(lenx - cr + cl)<5)
		{
			bcx = (cr + cl) >> 1;
			while (1)
			{
				bx = x - (x - bcx) * 2;
				by = y - (y - bcy) * 2;
				if (bx<2)
				{
					bx = 1;
					by = (bcy - y)*(bx - x) / (bcx - x) + y;
				}
				if (bx>IMG_W - 2)
				{
					bx = IMG_W - 1;
					by = (bcy - y)*(bx - x) / (bcx - x) + y;
				}
				if (by > IMG_H - 2)
				{
					by = IMG_H - 1;
					bx = (bcx - x)*(by - y) / (bcy - y) + x;
				}
				if (bx == 1 || bx == IMG_W - 1 || by == IMG_H - 1)
					break;
				if (IMAGE[by][bx]<Threshold)
				{
					flag = 0;
					for (cl = bx; IMAGE[by][cl] < Threshold; cl--)
					{
						if (cl <= 0 || cl <= bx - lenx)
						{
							flag |= 0x01;
							break;
						}
					}
					for (cr = bx; IMAGE[by][cr] < Threshold; cr++)
					{
						if (cr >= IMG_W || cr >= bx + lenx)
						{
							flag |= 0x02;
							break;
						}
					}
					if (flag)
						break;
					bx = (cr + cl) >> 1;
					if (_abs(lenx - cr + cl)<5 && isOnLine(bcx - x, bcy - y, bx - x, by - y))
					{
						bcx = bx; bcy = by;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			while (bcy + 1 < by)
			{
				short bccy = (by + bcy) / 2;
				short bccx = (bcx - x)*(bccy - y) / (bcy - y) + x;
				if (IMAGE[bccy][bccx]<Threshold)
				{
					flag = 0;
					for (cl = bccx; IMAGE[bccy][cl] < Threshold; cl--)
					{
						if (cl <= 0 || cl <= bccx - lenx)
						{
							flag |= 0x01;
							break;
						}
					}
					for (cr = bccx; IMAGE[bccy][cr] < Threshold; cr++)
					{
						if (cr >= IMG_W || cr >= bccx + lenx)
						{
							flag |= 0x02;
							break;
						}
					}
					if (flag)
					{
						bx = bccx; by = bccy;
					}
					else if (_abs(lenx - cr + cl) < 5)
					{
						bccx = (cl + cr) >> 1;
						if (isOnLine(bcx - x, bcy - y, bccx - x, bccy - y))
						{
							bcx = bccx; bcy = bccy;
						}
						else
						{
							bx = bccx; by = bccy;
						}
					}
					else
					{
						bx = bccx; by = bccy;
					}
				}
				else
				{
					bx = bccx; by = bccy;
				}
			}
			bx = bcx; by = bcy;
		}
		else
			return 0;

		if (by - ty>40)
		{
			if((ty<by && DirF==0) || (ty>by && DirF==1))
			{
				pLine->pt1x = tx; pLine->pt1y = ty;
				pLine->pt2x = bx; pLine->pt2y = by;
			}
			else
			{
				pLine->pt1x = bx; pLine->pt1y = by;
				pLine->pt2x = tx; pLine->pt2y = ty;
			}
			return 1;
		}
		else
		{
			return 0;
		}
	}

	if (leny <= lenx && leny < 30 && (dir&0x02))
	{
		short lx = x - 2, ly = y, rx = x + 2, ry = y;
		short lcx = x - 1, lcy = y, rcx = x + 1, rcy = y;
		y = (cb + ct) >> 1;
		flag = 0;
		for (ct = lcy; IMAGE[ct][lcx] < Threshold; ct--)
		{
			if (ct<=0 || ct <= lcy - leny)
			{
				flag |= 0x01;
				break;
			}
		}
		for (cb = lcy; cb < IMG_H && cb < lcy + leny && IMAGE[cb][lcx] < Threshold; cb++)
		{
			if (cb >= IMG_H || cb >= lcy + leny)
			{
				flag |= 0x02;
				break;
			}
		}
		if (flag==0 && _abs(leny - cb + ct)<5)
		{
			lcy = (cb + ct) >> 1;
			while (1)
			{
				lx = x - (x - lcx) * 2;
				ly = y - (y - lcy) * 2;
				if (lx<2)
				{
					lx = 1;
					ly = (lcy - y)*(lx - x) / (lcx - x) + y;
				}
				if (ly<2)
				{
					ly = 1;
					lx = (lcx - x)*(ly - y) / (lcy - y) + x;
				}
				if (ly>IMG_H - 2)
				{
					ly = IMG_H - 1;
					lx = (lcx - x)*(ly - y) / (lcy - y) + x;
				}
				if (lx == 1 || ly == 1 || ly == IMG_H - 1)
					break;
				if (IMAGE[ly][lx]<Threshold)
				{
					flag = 0;
					for (ct = ly; IMAGE[ct][lx] < Threshold; ct--)
					{
						if (ct <= 0 || ct <= ly - leny)
						{
							flag |= 0x01;
							break;
						}
					}
					for (cb = ly; IMAGE[cb][lx] < Threshold; cb++)
					{
						if (cb >= IMG_H || cb >= ly + leny)
						{
							flag |= 0x02;
							break;
						}
					}
					if (flag)
						break;
					ly = (cb + ct) >> 1;
					if (_abs(leny - cb + ct)<5 && isOnLine(lcx - x, lcy - y, lx - x, ly - y))
					{
						lcx = lx; lcy = ly;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}

			while (lcx > lx + 1)
			{
				short lccx = (lx + lcx) / 2;
				short lccy = (lcy - y)*(lccx - x) / (lcx - x) + y;
				if (IMAGE[lccy][lccx]<Threshold)
				{
					flag = 0;
					for (ct = lccy; IMAGE[ct][lccx] < Threshold; ct--)
					{
						if (ct<=0 || ct <= lccy - leny)
						{
							flag |= 0x01;
							break;
						}
					}
					for (cb = lccy; cb < IMG_H && cb < lccy + leny && IMAGE[cb][lccx] < Threshold; cb++)
					{
						if (cb >= IMG_H || cb >= lccy + leny)
						{
							flag |= 0x02;
							break;
						}
					}
					if (flag)
					{
						lx = lccx; ly = lccy;
					}
					else if (_abs(leny - cb + ct) < 5)
					{
						lccy = (ct + cb) >> 1;
						if (isOnLine(lcx - x, lcy - y, lccx - x, lccy - y))
						{
							lcx = lccx; lcy = lccy;
						}
						else
						{
							lx = lccx; ly = lccy;
						}
					}
					else
					{
						lx = lccx; ly = lccy;
					}
				}
				else
				{
					lx = lccx; ly = lccy;
				}
			}
			lx = lcx; ly = lcy;
		}
		else return 0;

		flag = 0;
		for (ct = rcy; ct > 0 && ct > rcy - leny && IMAGE[ct][rcx] < Threshold; ct--)
		{
			if (ct <= 0 || ct <= rcy - leny)
			{
				flag |= 0x01;
				break;
			}
		}
		for (cb = rcy; cb < IMG_H && cb < rcy + leny && IMAGE[cb][rcx] < Threshold; cb++)
		{
			if (cb >= IMG_H || cb >= rcy + leny)
			{
				flag |= 0x02;
				break;
			}
		}
		if (flag==0 && _abs(leny - cb + ct)<5)
		{
			rcy = (cb + ct) >> 1;
			while (1)
			{
				rx = x - (x - rcx) * 2;
				ry = y - (y - rcy) * 2;
				if (rx>IMG_W - 2)
				{
					rx = IMG_W - 1;
					ry = (rcy - y)*(rx - x) / (rcx - x) + y;
				}
				if (ry<2)
				{
					ry = 1;
					rx = (rcx - x)*(ry - y) / (rcy - y) + x;
				}
				if (ry>IMG_H - 2)
				{
					ry = IMG_H - 1;
					rx = (rcx - x)*(ry - y) / (rcy - y) + x;
				}
				if (rx == IMG_W - 1 || ry == 1 || ry == IMG_H - 1)
					break;
				if (IMAGE[ry][rx]<Threshold)
				{
					flag = 0;
					for (ct = ry; IMAGE[ct][rx] < Threshold; ct--)
					{
						if (ct<=0 || ct <= ry - leny)
						{
							flag |= 0x01;
							break;
						}
					}
					for (cb = ry; IMAGE[cb][rx] < Threshold; cb++)
					{
						if (cb >= IMG_H || cb >= ry + leny)
						{
							flag |= 0x02;
							break;
						}
					}
					if (flag)
						break;
					ry = (cb + ct) >> 1;
					if (_abs(leny - cb + ct)<5 && isOnLine(rcx - x, rcy - y, rx - x, ry - y))
					{
						rcx = rx; rcy = ry;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			while (rcx + 1 < rx)
			{
				short rccx = (rx + rcx) / 2;
				short rccy = (rcy - y)*(rccx - x) / (rcx - x) + y;
				if (IMAGE[rccy][rccx]<Threshold)
				{
					flag = 0;
					for (ct = rccy; IMAGE[ct][rccx] < Threshold; ct--)
					{
						if (ct<=0 || ct <= rccy - leny)
						{
							flag |= 0x01;
							break;
						}
					}
					for (cb = rccy; IMAGE[cb][rccx] < Threshold; cb++)
					{
						if (cb >= IMG_H || cb >= rccy + leny)
						{
							flag |= 0x02;
							break;
						}
					}
					if (flag)
					{
						rx = rccx; ry = rccy;
					}
					else if (_abs(leny - cb + ct) < 5)
					{
						rccy = (ct + cb) >> 1;
						if (isOnLine(rcx - x, rcy - y, rccx - x, rccy - y))
						{
							rcx = rccx; rcy = rccy;
						}
						else
						{
							rx = rccx; ry = rccy;
						}
					}
					else
					{
						rx = rccx; ry = rccy;
					}
				}
				else
				{
					rx = rccx; ry = rccy;
				}
			}
			rx = rcx; ry = rcy;
		}
		else
			return 0;


		if (rx - lx>40)
		{
			if((ly<ry && DirF==0) || (ly>ry && DirF==1))
			{
				pLine->pt1x = lx; pLine->pt1y = ly;
				pLine->pt2x = rx; pLine->pt2y = ry;
			}
			else
			{
				pLine->pt1x = rx; pLine->pt1y = ry;
				pLine->pt2x = lx; pLine->pt2y = ly;
			}
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

uint8_t CheckLineY(void)
{
	uint16_t m, n, a, b, c, w;
	w = IMG_H;
	for (a = 2; w / a >= 8; a *= 2)
	{
		for (b = 1; b < a; b += 2)
		{
			for(c=1; c<a; c+=2)
			{
				m=IMG_W*b/a;
				n=IMG_H*c/a;
				if(CheckLine(m,n,img.Line,40,0x01))
					return 1;
			}
		}
	}
	img.Line[0].pt1x=0;img.Line[0].pt1y=0;img.Line[0].pt2x=0;img.Line[0].pt2y=0;
	return 0;
}



uint8_t CheckLineX(void)
{
	uint16_t m, n, a, b, c, w;
	w = IMG_H;
	for (a = 2; w / a >= 8; a *= 2)
	{
		for (b = 1; b < a; b += 2)
		{
			for(c=1; c<a; c+=2)
			{
				m=IMG_W*b/a;
				n=IMG_H*c/a;
				if(CheckLine(m,n,img.Line+1,40,0x02))
					return 1;
			}
		}
	}
	img.Line[1].pt1x=0;img.Line[1].pt1y=0;img.Line[1].pt2x=0;img.Line[1].pt2y=0;
	return 0;
}


void CameraRun(void)
{
	static uint8_t rate=0;
	static u32 Tm;
	static uint8_t STATE=0;
	if(Tm+1000<get_timer())
	{
		Tm=get_timer();
		img.rate=rate;
		rate=0;
	}
	switch (STATE)
	{
		case 0:
			if(DCMI_FINSH)
			{
				rate++;
				img.time=get_timer();
				GetCenter();
//				STATE=2;
			 DCMI_FINSH=0;

//			 GetBitImage(aTxBuffer+sizeof(Data_Type));

			 DCMI_Start();
			 STATE=0;
			 img.update = 1;
			}
			break;
		case 1:
		{
//			CheckLineY();
//			CheckLineX();
			STATE=2;
		}break;
		case 2:
		{
//			
//			DCMI_FINSH=0;
//			DCMI_Start();
			STATE=0;
		}break;
		default:
		{
			STATE=0;
		}break;
	}
}


void GetBitImage(void *pbuf)
{
	uint16_t i,j,k;
	uint8_t da;
	uint8_t (*p)[10]=pbuf;
	for(i=0;i<60;i++)
	{
		for(j=0;j<10;j++)
		{
			da=0;
			for(k=0;k<8;k++)
			{
				if(IMAGE[i*4][j*32+k*4]>Threshold)
					da|=(0x80>>k);
			}
			p[i][j]=da;
		}
	}
	PutPixel(pbuf,img.CerPtx/4,img.CerPty/4);
	PutPixel(pbuf,img.CerPtx/4+1,img.CerPty/4);
	PutPixel(pbuf,img.CerPtx/4,img.CerPty/4+1);
	PutPixel(pbuf,img.CerPtx/4+1,img.CerPty/4+1);
//	LCD_DrawUniLine(pbuf,img.Line[0].pt1x/4,img.Line[0].pt1y/4,img.Line[0].pt2x/4,img.Line[0].pt2y/4);
//	LCD_DrawUniLine(pbuf,img.Line[1].pt1x/4,img.Line[1].pt1y/4,img.Line[1].pt2x/4,img.Line[1].pt2y/4);
}


void PutPixel(void *pbuf, uint16_t x, uint16_t y)
{
	uint8_t (*p)[10]=pbuf;
	p[y][x/8]^=0x80>>(x%8);
}



