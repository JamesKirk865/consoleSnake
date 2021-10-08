#include<iostream>
#include<conio.h>
#include<thread>
#include<windows.h>
#include<time.h>
#include<fstream>
#include<vector>

const int M=20,N=20;//M - y, N - x
int len=1,sn[2][666],r;
char inert='d',mvmnt='d';
char map[M][N];
std::string add/*addition*/,level="borderless.txt";

void start(){
	sn[0][0]=M/2;
	sn[1][0]=N/2-1;
	sn[0][1]=M/2;
	sn[1][1]=N/2;
	len=1;
	mvmnt='d';
	inert='d';
}

int rndm(int base){
	std::string res=std::to_string((42*base+4327)%10000000);
	res=res.substr(0,strlen(res.c_str())-1);
	return atoi(res.c_str());
}

void spawn(){
	int x,y;
	while(true){
		r=rndm(r);
		x=r%(M-2)+1;
		r=rndm(r);
		y=r%(N-2)+1;
		if(map[y][x]=='0'){
			map[y][x]='3';
		break;
		}
	}
}

bool move(){
	switch(mvmnt){
		int x,y;
		case 'w':
			inert='w';
			if(map[sn[1][len]-1][sn[0][len]]=='3'){
				map[sn[1][len]-1][sn[0][len]]='1';
				sn[0][len+1]=sn[0][len];
				sn[1][len+1]=sn[1][len]-1;
				len++;
				spawn();
			}else{
				if(sn[1][len]==0){
					if(map[M-1][sn[0][len]]!='0')
						return false;
				}else{
					if(map[sn[1][len]-1][sn[0][len]]!='0')
						return false;
				}
				map[sn[1][0]][sn[0][0]]='0';
				for(int i=0;i<len;++i){
					sn[0][i]=sn[0][i+1];
					sn[1][i]=sn[1][i+1];
				}
				if(sn[1][len]==0){
					sn[1][len]=M-1;
					map[sn[1][len]][sn[0][len]]='1';
				}else{
					map[--sn[1][len]][sn[0][len]]='1';
				}
			}
		break;
		case 'a':
			inert='a';
			if(map[sn[1][len]][sn[0][len]-1]=='3'){
				map[sn[1][len]][sn[0][len]-1]='1';
				sn[0][len+1]=sn[0][len]-1;
				sn[1][len+1]=sn[1][len];
				len++;
				spawn();
			}else{
				if(sn[0][len]==0){
					if(map[sn[1][len]][N-1]!='0')
						return false;
				}else{
					if(map[sn[1][len]][sn[0][len]-1]!='0')
						return false;
				}
				map[sn[1][0]][sn[0][0]]='0';
				for(int i=0;i<len;++i){
					sn[0][i]=sn[0][i+1];
					sn[1][i]=sn[1][i+1];
				}
				if(sn[0][len]==0){
					sn[0][len]=N-1;
					map[sn[1][len]][sn[0][len]]='1';
				}else{
					map[sn[1][len]][--sn[0][len]]='1';
				}
			}
		break;
		case 's':
			inert='s';
			if(map[sn[1][len]+1][sn[0][len]]=='3'){
				map[sn[1][len]+1][sn[0][len]]='1';
				sn[0][len+1]=sn[0][len];
				sn[1][len+1]=sn[1][len]+1;
				len++;
				spawn();
			}else{
				if(sn[1][len]==(M-1)){
					if(map[0][sn[0][len]]!='0')
						return false;
				}else{
					if(map[sn[1][len]+1][sn[0][len]]!='0')
						return false;
				}
				map[sn[1][0]][sn[0][0]]='0';
				for(int i=0;i<len;++i){
					sn[0][i]=sn[0][i+1];
					sn[1][i]=sn[1][i+1];
				}
				if(sn[1][len]==(M-1)){
					sn[1][len]=0;
					map[sn[1][len]][sn[0][len]]='1';
				}else{
					map[++sn[1][len]][sn[0][len]]='1';
				}
			}
		break;
		case 'd':
			inert='d';
			if(map[sn[1][len]][sn[0][len]+1]=='3'){
				map[sn[1][len]][sn[0][len]+1]='1';
				sn[0][len+1]=sn[0][len]+1;
				sn[1][len+1]=sn[1][len];
				len++;
				spawn();
			}else{
				if(sn[0][len]==(N-1)){
					if(map[sn[1][len]][0]!='0')
						return false;
				}else{
					if(map[sn[1][len]][sn[0][len]+1]!='0')
						return false;
				}
				map[sn[1][0]][sn[0][0]]='0';
				for(int i=0;i<len;++i){
					sn[0][i]=sn[0][i+1];
					sn[1][i]=sn[1][i+1];
				}
				if(sn[0][len]==(N-1)){
					sn[0][len]=0;
					map[sn[1][len]][sn[0][len]]='1';
				}else{
					map[sn[1][len]][++sn[0][len]]='1';
				}
			}
		break;
	}
return true;
}

void gotoxy(int xpos, int ypos){
	COORD scrn;    
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput,scrn);
}

void draw(){
	std::string out;
	for(int i=0;i<20;++i)
		for(int j=0;j<20;++j)
			switch(map[i][j]){
				case '0'://nothing
					out+="  ";
				break;
				case '1'://snake
					out+=(char)177;
					out+=(char)177;
				break;
				case'2'://wall
					out+=(char)178;
					out+=(char)178;
				break;
				case'3'://apple
					out+=(char)17;
					out+=(char)16;
				break;
			}
	//system("cls");
	gotoxy(0,0);
	std::cout<<out;
}

void drawMenu(int p,bool pl){
	std::string res;
	if(pl)
		res="[ ]continue\n[ ]select level\n[ ]exit";
	else
		res="[ ]new game\n[ ]select level\n[ ]exit";
	switch(p){
		case 1:	res[1]='x';		break;
		case 2:	res[13]='x';	break;
		case 3:	res[29]='x';	break;
	}
	system("cls");
	//gotoxy(0,0);
	std::cout<<add+res;
}

void resizeCmd(){
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024);
    hwnd=FindWindow(NULL, Title);
    MoveWindow(hwnd,100,100,320,358,TRUE);//100/100/320/358 - 20 строк, 40 столбцов
}

bool loadLevel(std::string name){
	name="./levels/"+name;
	std::fstream f;
	char B[100];
	f.open(name.c_str(),std::ios_base::in);
	if(!f.is_open())
		return false;
	for(int i=0;i<M;++i){
		f.getline(B,100);
		for(int j=0;j<N;++j)
			map[i][j]=B[j];
	}
	f.close();
return true;
}

std::string selectLevel(){
	WIN32_FIND_DATA Fdat;
	std::vector<std::string>list;
	std::string s;
	int j=-1,curr=0;
	HANDLE h = FindFirstFile("./levels/*.txt", &Fdat);
	if(h==INVALID_HANDLE_VALUE){
		return 0;
	}else{
		do{
			list.push_back(Fdat.cFileName);
			j++;
		}while(FindNextFile(h,&Fdat));
	}
	system("cls");
	for(int i=0;i<list.size();++i){
		std::cout<<"[ ]"<<list[i]<<std::endl;
		if(level==list[i])
			curr=i;
	}
	char c;
	gotoxy(1,curr);
	std::cout<<"x";
	gotoxy(list[j].length()+3,list.size()-1);
	while(true){
		c=getch();
		gotoxy(1,curr);
		std::cout<<" ";
		switch(c){
			case 'w':
				if(curr>0)
					curr--;
			break;
			case 's':
				if(curr<list.size()-1)
					curr++;
			break;
			case ' ':
				return list[curr];
			break;
		}
		gotoxy(1,curr);
		std::cout<<"x";
		gotoxy(list[j].length()+3,list.size()-1);
	}
};

int main(){
	bool run=true,pause=true,play=false;
	clock_t t=0;
	SYSTEMTIME st;
	GetLocalTime(&st);
	r=st.wSecond+st.wMilliseconds;
	start();
	char c;
	int line=1,lMax=3,lMin=1;
	std::thread console([&](){
		int i;
		while(run){
			if(!pause){
				if(!play){
					play=true;
					start();
					loadLevel(level);
					spawn();
					add="";
				}
				if((clock()-t)>250){
					t=clock();
					draw();
					if(!move()){
						Sleep(500);
						add="you lose\ncollected apples: "+std::to_string(len-1)+"\n\n";
						pause=true;
						play=false;
					}
					Sleep(50);
				}
			}else{
				drawMenu(line,play);
				c=getch();
				switch(c){
					case 'w':
						if(line!=lMin)
							line--;
					break;
					case 's':
						if(line!=lMax)
							line++;
					break;
					case ' ':
						switch(line){
							case 1:
								pause=false;
							break;
							case 2:
								play=false;
								level=selectLevel();
								loadLevel(level);
								add="";
							break;
							case 3:
								run=false;
							break;
						}
					break;
				}
				c='-';
			}
		}
	});
	std::thread input([&](){
		char k;
		while(run){
			if(pause){
				Sleep(50);
			}else{
				if(play)
					k=getch();
				switch(k){
					case 'w':
						if(inert!='s')
							mvmnt='w';
					break;
					case 'a':
						if(inert!='d')
							mvmnt='a';
					break;
					case 's':
						if(inert!='w')
							mvmnt='s';
					break;
					case 'd':
						if(inert!='a')
							mvmnt='d';
					break;
				}
				Sleep(50);
			}
			if(k==' '){
				pause=true;
				k=mvmnt;
			}
		}
	});
	resizeCmd();
	console.join();
	input.join();
return 0;
}