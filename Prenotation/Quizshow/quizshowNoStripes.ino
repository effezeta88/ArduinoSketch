#define LED_BLUE 5
#define LED_RED 4
#define LED_GREEN 7
#define LED_YELLOW 5
#define BUTTON_BLUE 2
#define BUTTON_RED 3
#define BUTTON_GREEN 6
#define BUTTON_YELLOW 2
#define NUM 3

int val[NUM];
int status_Led[NUM];
int isblink[NUM];
int tm_start[NUM];
int LED_[NUM];
int BTN_[NUM];

void setup() {
  Serial.begin(9600);
  load_led(LED_,NUM);
  load_btn(BTN_,NUM);
  //Inizialize Led and status of each one
  Inizialize(status_Led,NUM,0);
  Inizialize(isblink,NUM,-1);
  Inizialize(tm_start,NUM,-1);
  Inizialize(val,NUM,0);
  
}

void loop(){

  for(int i=0;i<NUM;i++){
    // check the status of each led and set a number of priority in order to indicate the priority
    if(status_Led[i]==0) 
    {
      val[i]= digitalRead(BTN_[i]);  // read input value
      if(val[i]==1){
          tm_start[i]=millis();
          status_Led[i]=1;
          int sum_ = somma(val,NUM,i);
          if(sum_==0){
              isblink[i]=0;
          }else if(sum_==1){
              isblink[i]=1;
          }
          else if(sum_==2 && isblink[i]==-1){
              isblink[i]=2;
          }
      }
    }
  }
  
  //Lights on and off the LED following the priority
  for(int i=0;i<NUM;i++){
     if(status_Led[i]==1){
       int timeblink=1;
       if(isblink[i]==1)
          timeblink=150;
       else if (isblink[i]==2)
          timeblink=1000;
       if((millis()-tm_start[i])%(timeblink*2)<=timeblink)
         digitalWrite(LED_[i],HIGH);
       else
         digitalWrite(LED_[i],LOW);
    }
  }
}

void Inizialize(int v[], int size, int val){
  for(int i=0;i<size;i++){
    v[i]=val;
  }
}

void load_led(int v[],int size){
    v[0]= LED_BLUE;
    v[1]= LED_RED;
    v[2]= LED_GREEN;
    for(int i=0;i<size;i++){
      pinMode(v[i],OUTPUT);
    }
}

int somma(int v[],int size, int j){
  int somma=0;
    for(int i=0;i<size;i++){
      if(i!=j)
        somma=somma+v[i];
    }
    return somma;
}

void load_btn(int v[],int size){
    v[0]= BUTTON_BLUE;
    v[1]= BUTTON_RED;
    v[2]= BUTTON_GREEN;
    for(int i=0;i<size;i++){
      pinMode(v[i],INPUT);
    }
}
 
