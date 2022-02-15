
void setup() {

}
unsigned short RH_Module_checkSum(unsigned char *Buff,unsigned char Len){ 

  unsigned short a_temp_crc =0xFFFF;
  unsigned char i;
  while(Len--){
    a_temp_crc ^=*Buff++;
    for(i=0; i<8;i++){
      if(a_temp_crc & 0x01){
          a_temp_crc >>=1;
          a_temp_crc ^=0xA001;
        }else{
            a_temp_crc >> 1;
          }
      }
    
    }
    return a_temp_crc;
}
void loop(){}
