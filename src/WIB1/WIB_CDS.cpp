#include "wibmod/WIB1/WIB.hh"
#include <unistd.h> // usleep

#include "wibmod/WIB1/WIBException.hh"

#define COURSE_DATARATE_SIZE 232
static float courseDataRates[COURSE_DATARATE_SIZE] = {5.3745e+06,5.3741e+06,5.4793e+06,5.5912e+06,5.7111e+06,5.8391e+06,5.9760e+06,6.1215e+06,6.2780e+06,6.4565e+06,6.6391e+06,6.8372e+06,7.0520e+06,7.2868e+06,7.5424e+06,7.8220e+06,7.6663e+06,7.6659e+06,7.8217e+06,7.9880e+06,8.1667e+06,8.3570e+06,8.5616e+06,8.7805e+06,9.0166e+06,9.2849e+06,9.5608e+06,9.8591e+06,1.0183e+07,1.0535e+07,1.0918e+07,1.1332e+07,1.0749e+07,1.0748e+07,1.0959e+07,1.1182e+07,1.1422e+07,1.1678e+07,1.1952e+07,1.2243e+07,1.2556e+07,1.2913e+07,1.3278e+07,1.3674e+07,1.4104e+07,1.4574e+07,1.5085e+07, 
1.5644e+07,1.5333e+07,1.5332e+07,1.5643e+07,1.5976e+07,1.6333e+07,1.6714e+07,1.7123e+07,1.7561e+07,1.8033e+07,1.8570e+07,1.9122e+07,1.9718e+07,2.0367e+07,2.1070e+07,2.1835e+07,2.2664e+07,2.1498e+07,2.1496e+07,2.1917e+07,2.2365e+07,2.2844e+07,2.3357e+07,2.3904e+07,2.4486e+07,2.5112e+07,2.5826e+07,2.6556e+07,2.7349e+07,2.8208e+07,2.9147e+07,3.0170e+07,3.1288e+07,3.0665e+07,3.0664e+07,3.1287e+07,3.1952e+07,3.2667e+07,3.3428e+07,3.4246e+07,3.5122e+07,3.6066e+07,3.7140e+07,3.8243e+07,3.9436e+07,4.0733e+07,4.2140e+07, 
4.3671e+07,4.5328e+07,4.2996e+07,4.2993e+07,4.3834e+07,4.4729e+07,4.5688e+07,4.6713e+07,4.7808e+07,4.8972e+07,5.0224e+07,5.1652e+07,5.3113e+07,5.4698e+07,5.6416e+07,5.8295e+07,6.0339e+07,6.2576e+07,6.1331e+07,6.1328e+07,6.2574e+07,6.3904e+07,6.5334e+07,6.6856e+07,6.8493e+07,7.0244e+07,7.2133e+07,7.4279e+07,7.6486e+07,7.8872e+07,8.1467e+07,8.4279e+07,8.7341e+07,9.0657e+07,8.5991e+07,8.5986e+07,8.7668e+07,8.9458e+07,9.1377e+07,9.3426e+07,9.5616e+07,9.7944e+07,1.0045e+08,1.0330e+08,1.0623e+08,1.0940e+08,1.1283e+08, 
1.1659e+08,1.2068e+08,1.2515e+08,1.2266e+08,1.2266e+08,1.2515e+08,1.2781e+08,1.3067e+08,1.3371e+08,1.3699e+08,1.4049e+08,1.4427e+08,1.4856e+08,1.5297e+08,1.5774e+08,1.6293e+08,1.6856e+08,1.7468e+08,1.8131e+08,1.7198e+08,1.7197e+08,1.7534e+08,1.7892e+08,1.8275e+08,1.8685e+08,1.9123e+08,1.9589e+08,2.0089e+08,2.0661e+08,2.1245e+08,2.1879e+08,2.2566e+08,2.3318e+08,2.4136e+08,2.5030e+08,2.4532e+08,2.4531e+08,2.5029e+08,2.5562e+08,2.6134e+08,2.6742e+08,2.7397e+08,2.8098e+08,2.8853e+08,2.9712e+08,3.0594e+08,3.1549e+08, 
3.2587e+08,3.3712e+08,3.4936e+08,3.6263e+08,3.4397e+08,3.4394e+08,3.5067e+08,3.5783e+08,3.6551e+08,3.7370e+08,3.8247e+08, 
3.9177e+08,4.0179e+08,4.1322e+08,4.2490e+08,4.3758e+08,4.5133e+08,4.6636e+08,4.8272e+08,5.0061e+08,4.9064e+08,4.9062e+08, 
5.0059e+08,5.1123e+08,5.2267e+08,5.3485e+08,5.4794e+08,5.6195e+08,5.7706e+08,5.9423e+08,6.1189e+08,6.3098e+08,6.5173e+08, 
				     6.7423e+08,6.9873e+08,7.2525e+08,6.8793e+08,6.8789e+08,7.0135e+08,7.1567e+08,7.3102e+08,7.4741e+08,7.6493e+08,7.8355e+08};


void WIB::WriteDTS_CDS(uint16_t address,uint32_t value,uint8_t byte_count,bool ignore_error){
  WriteI2C("DTS.CDS.I2C",address,value,byte_count,ignore_error);
}
uint32_t WIB::ReadDTS_CDS(uint16_t address,uint8_t byte_count){
  return ReadI2C("DTS.CDS.I2C",address,byte_count);
}

float WIB::ConfigureDTSCDS(uint8_t source){
  if(source > 1){
    BUException::WIB_BAD_ARGS e;
    e.Append("Bad DTS CDS clock source");
    throw e;
  }

  //Set timing system source (FP:0 BP:1)
  WriteWithRetry("DTS.CDS.INPUT_SELECT",source);

  //Reset the I2C firmware
  WriteWithRetry("DTS.CDS.I2C.RESET",1);
  //Reset the CDS chip (ADN2814)  
  WriteDTS_CDS(0x9,0x20,1);
  usleep(500000);

  //Reset the I2C firmware
  WriteWithRetry("DTS.CDS.I2C.RESET",1);
  //Un reset
  WriteDTS_CDS(0x9,0x00,1,true);
  //Reset the I2C firmware
  WriteWithRetry("DTS.CDS.I2C.RESET",1);
  usleep(1000000);

  //read bits 8 downto 1 from reg 3
  uint16_t dataRateLookup = uint16_t(ReadDTS_CDS(0x3,1)) << 1;
  //Read bit 0 from reg 4
  dataRateLookup |= uint16_t(ReadDTS_CDS(0x4,1))&0x1;
  if(dataRateLookup >=COURSE_DATARATE_SIZE){
    return -1;
  }
  return courseDataRates[dataRateLookup];
}
