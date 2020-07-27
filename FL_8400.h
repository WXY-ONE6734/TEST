#ifndef _FL_8400_H_
#define _FL_8400_H_

#define uchar unsigned char 
#define uint unsigned int

sbit SSDA=P3^7;

void SendData ( uchar addr );
void ONE_LINE_VOL(uchar vol);
void ONE_LINE_PLAY();
void ONE_LINE_PAUSE();
void ONE_LINE_STOP();
void ONE_LINE_PLAY_SONG(uchar song);
void ONE_LINE_NEXT();
void delay_us(uint x);

void delay_us(uint x)//延时语音
{while(x--); }


//设置音量：vol（0-30）
void ONE_LINE_VOL(uchar vol)
{
    if(vol>30)vol=30;
    SendData(vol/10);
    SendData(vol%10);
    SendData(0x0C);
}

//指定曲目播放        song: (1-255)
void ONE_LINE_PLAY_SONG(uchar song)
{
    uchar i;
    uchar tmp[3];
    
    tmp[0]=song/100;song%=100;
    tmp[1]=song/10;
    tmp[2]=song%10;
    
    SendData(0x0a);
    for(i=0;i<3;i++)
    {
       if(tmp[i]!=0)
       {
          SendData(tmp[i]);
       }   
    }
    SendData(0x0b);
    
}
void SendData( uchar addr )//发送函数。
{
    uchar i;
    EA = 0;
    SSDA = 1;
    delay_us ( 1000 );
    SSDA = 0;
    delay_us ( 2000 );
    for ( i = 0; i < 8; i++ ) 
    {SSDA = 1;
    if ( addr & 0x01 ) 
    {delay_us ( 1200 );
    SSDA = 0;
    delay_us ( 400 );}
    else 
    {delay_us ( 400 );
     SSDA = 0;
     delay_us ( 1200 );}
     addr >>= 1;}
     SSDA = 1;
     EA = 1;
}


#endif