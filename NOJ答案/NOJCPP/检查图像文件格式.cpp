#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
struct head { unsigned char b; long count; long parent,lch,rch; char bits[256]; }header[512],tmp;
void compress() {
char filename[255],outputfile[255],buf[512];
unsigned char c;
long n,m,i,j,f;
 long min1,pt1,flength=0,length1,length2;
double div;
 FILE *ifp,*ofp;
printf("\t 请您输入需要压缩的文件（需要路径） ：");
gets(filename);
ifp=fopen(filename,"rb");
      if(ifp==NULL){
 printf("\n\t 文件打开失败!\n ");
system("pause");
 return;
} printf("\t 请您输入压缩后的文件名（如无路径则默认为桌面文件） ：");
gets(outputfile);
 ofp=fopen(outputfile,"wb");
if(ofp==NULL){
 printf("\n\t 压缩文件失败!\n ");
 system("pause");
return;
} flength=0;
 while(!feof(ifp)){
 fread(&c,1,1,ifp);
header[c].count++;
 flength++;
 } flength--;
length1=flength;
header[c].count--;
 for(i=0;i<512;i++){
 if(header[i].count!=0) header[i].b=(unsigned char)i;
 else header[i].b=0;
header[i].parent=-1;
header[i].lch=header[i].rch=-1;
 }
for(i=0;i<256;i++){
 for(j=i+1;j<256;j++){
 if(header[i].count<header[j].count){
 tmp=header[i];
header[i]=header[j];
 header[j]=tmp;
 }
}
 } for(i=0;i<256;i++) if(header[i].count==0)
break;
n=i;
m=2*n-1;
for(i=n;i<m;i++){
 min1=999999999;
 for(j=0;j<i;j++){
 if(header[j].parent!=-1) continue;
if(min1>header[j].count){
 pt1=j;
 min1=header[j].count;
 continue;
}
}
header[i].count=header[pt1].count;
 header[pt1].parent=i;
header[i].lch=pt1;
 min1=999999999;
for(j=0;j<i;j++){
 if(header[j].parent!=-1) continue;
 if(min1>header[j].count){
 pt1=j;
min1=header[j].count;
 continue;
}
} header[i].count+=header[pt1].count;
header[i].rch=pt1;
 header[pt1].parent=i;
 } for(i=0;i<n;i++){
 f=i;
header[i].bits[0]=0;
 while(header[f].parent!=-1){
j=f;
f=header[f].parent;
 if(header[f].lch==j){
 j=strlen(header[i].bits);
memmove(header[i].bits+1,header[i].bits,j+1); //依次存储连接"0""1"编码，此处语句为网络借鉴 header[i].bits[0]='0';
 }
else{
      j=strlen(header[i].bits);
 memmove(header[i].bits+1,header[i].bits,j+1);
 header[i].bits[0]='1';
}
}
 } fseek(ifp,0,SEEK_SET);
fwrite(&flength,sizeof(int),1,ofp);
fseek(ofp,8,SEEK_SET);
 buf[0]=0;
f=0;
 pt1=8;
 while(!feof(ifp)){
 c=fgetc(ifp);
 f++;
for(i=0;i<n;i++){
if(c==header[i].b) break;
} strcat(buf,header[i].bits);
j=strlen(buf);
c=0;
 while(j>=8){
 for(i=0;i<8;i++){
 if(buf[i]=='1') c=(c<<1)|1;
 else c=c<<1;
} fwrite(&c,1,1,ofp);
 pt1++;
 strcpy(buf,buf+8);
 j=strlen(buf);
} if(f==flength) break;
} if(j>0){ strcat(buf,"00000000");
for(i=0;i<8;i++){
 if(buf[i]=='1') c=(c<<1)|1;
      else c=c<<1;
} fwrite(&c,1,1,ofp);
 pt1++;
} fseek(ofp,4,SEEK_SET);
 fwrite(&pt1,sizeof(long),1,ofp);
 fseek(ofp,pt1,SEEK_SET);
 fwrite(&n,sizeof(long),1,ofp);
for(i=0;i<n;i++){
fwrite(&(header[i].b),1,1,ofp);
 c=strlen(header[i].bits);
 fwrite(&c,1,1,ofp);
j=strlen(header[i].bits);
 if(j%8!=0){
for(f=j%8;f<8;f++) strcat(header[i].bits,"0");
 } while(header[i].bits[0]!=0){
 c=0; for(j=0;j<8;j++){
 if(header[i].bits[j]=='1') c=(c<<1)|1;
else c=c<<1;
}
strcpy(header[i].bits,header[i].bits+8);
 fwrite(&c,1,1,ofp);
}
 }
length2=pt1--;
div=((double)length1-(double)length2)/(double)length1;
fclose(ifp);
 fclose(ofp);
 printf("\n\t 压缩文件成功!\n");
printf("\t 压缩率为 %f%%\n\n",div*100);
 return;
 }
void uncompress(){
 char filename[255],outputfile[255],buf[255],bx[255];
unsigned char c;
long i,j,m,n,f,p,l;
 long flength;
FILE *ifp,*ofp;
 printf("\t 请您输入需要解压缩的文件（如无路径则默认为桌面文件） ：");
gets(filename);
ifp=fopen(filename,"rb");
if(ifp==NULL){ printf("\n\t 文件打开失败!\n ");
 system("pause"); return; } printf("\t 请您输入解压缩后的文件名：");
 gets(outputfile);
ofp=fopen(outputfile,"wb");
if(ofp==NULL){
 printf("\n\t 解压缩文件失败!\n ");
 system("pause");
return;
} fread(&flength,sizeof(long),1,ifp);
 fread(&f,sizeof(long),1,ifp);
 fseek(ifp,f,SEEK_SET);
fread(&n,sizeof(long),1,ifp);
 for(i=0;i<n;i++){
 fread(&header[i].b,1,1,ifp);
fread(&c,1,1,ifp);
 p=(long)c;
header[i].count=p;
header[i].bits[0]=0;
if(p%8>0) m=p/8+1;
 else m=p/8;
 for(j=0;j<m;j++){ fread(&c,1,1,ifp);
f=c;
itoa(f,buf,2);
 f=strlen(buf);
for(l=8;l>f;l--){ strcat(header[i].bits,"0");
}
strcat(header[i].bits,buf);
      } header[i].bits[p]=0;
} for(i=0;i<n;i++){
 for(j=i+1;j<n;j++){
if(strlen(header[i].bits)>strlen(header[j].bits)){
tmp=header[i];
header[i]=header[j];
header[j]=tmp;
 }
 }
 } p=strlen(header[n-1].bits);
fseek(ifp,8,SEEK_SET);
 m=0; bx[0]=0;
 while(1){
 while(strlen(bx)<(unsigned int)p){
 fread(&c,1,1,ifp);
 f=c;
 itoa(f,buf,2);
 f=strlen(buf);
for(l=8;l>f;l--){
 strcat(bx,"0");
 } strcat(bx,buf);
} for(i=0;i<n;i++){
 if(memcmp(header[i].bits,bx,header[i].count)==0) break;
 }
 strcpy(bx,bx+header[i].count);
c=header[i].b;
 fwrite(&c,1,1,ofp);
m++;
if(m==flength) break;
} fclose(ifp);
 fclose(ofp);
printf("\n\t 解压缩文件成功!\n");
 if(m==flength)printf("\t 解压缩文件与原文件相同!\n\n");
else printf("\t 解压缩文件与原文件不同!\n\n"); return;
 }
 int main(){
int c;
while(1){
printf("\tHuffman 前缀编码 压缩＆解压缩 BY ******** **\n");
printf("\t1.压缩 2.解压缩 0.退出\n");
 do{ printf("\n\t*请选择相应功能编号(0-2):");
 c=getch();
printf("%c\n",c); if(c!='0' && c!='1' && c!='2'){
printf("\t 请检查您的输入在 0~2 之间！ 请再输入一遍！\n");
}
}
while(c!='0' && c!='1' && c!='2');
if(c=='1') compress();
 else if(c=='2') uncompress();
 else{ exit(0);
}
system("pause");
system("cls");
 }
return 0;
}
