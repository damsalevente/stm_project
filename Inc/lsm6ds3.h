/*FUNC_CFG_ACCESS r/w 01 00000001 00000000
  SENSOR_SYNC_TIME_
  FRAME r/w 04 00000100 00000000
  FIFO_CTRL1 r/w 06 00000110 00000000
  FIFO_CTRL2 r/w 07 00000111 00000000
  FIFO_CTRL3 r/w 08 00001000 00000000
  FIFO_CTRL4 r/w 09 00001001 00000000
  FIFO_CTRL5 r/w 0A 00001010 00000000
  ORIENT_CFG_G r/w 0B 00001011 00000000
  INT1_CTRL r/w 0D 00001101 00000000 INT1 pin control
  INT2_CTRL r/w 0E 00001110 00000000 INT2 pin control
  WHO_AM_I r 0F 00001111 01101001 Who I am ID
  CTRL1_XL r/w 10 00010000 00000000
  CTRL2_G r/w 11 00010001 00000000
  CTRL3_C r/w 12 00010010 00000100
  CTRL4_C r/w 13 00010011 00000000
  CTRL5_C r/w 14 00010100 00000000
  CTRL6_C r/w 15 00010101 00000000
  CTRL7_G r/w 16 00010110 00000000
  CTRL8_XL r/w 17 0001 0111 00000000
  CTRL9_XL r/w 18 00011000 00111000
  CTRL10_C r/w 19 00011001 00111000 */

#define RAM_ACCESS            0x01
#define SENSOR_SYNC_TIME      0x04
#define SENSOR_SYNC_EN        0x05
#define FIFO_CTRL1            0x06
#define FIFO_CTRL2            0x07
#define FIFO_CTRL3            0x08
#define FIFO_CTRL4            0x09
#define FIFO_CTRL5            0x0A
#define ORIENT_CFG_G          0x0B
#define REFERENCE_G           0x0C
#define INT1_CTRL             0x0D
#define INT2_CTRL             0x0E
#define WHO_AM_I_REG          0X0F
#define CTRL1_XL              0x10
#define CTRL2_G               0x11
#define CTRL3_C               0x12
#define CTRL4_C               0x13
#define CTRL5_C               0x14
#define CTRL6_C               0x15
#define CTRL7_G               0x16
#define CTRL8_XL              0x17
#define CTRL9_XL              0x18
#define CTRL10_C              0x19
#define MASTER_CONFIG         0x1A
#define WAKE_UP_SRC           0x1B
#define TAP_SRC               0x1C
#define D6D_SRC               0x1D
#define STATUS_REG            0x1E
#define OUT_TEMP_L            0x20
#define OUT_TEMP_H            0x21
#define OUTX_L_G              0x22
#define OUTX_H_G              0x23
#define OUTY_L_G              0x24
#define OUTY_H_G              0x25
#define OUTZ_L_G              0x26
#define OUTZ_H_G              0x27
#define OUTX_L_XL             0x28
#define OUTX_H_XL             0x29
#define OUTY_L_XL             0x2A
#define OUTY_H_XL             0x2B
#define OUTZ_L_XL             0x2C
#define OUTZ_H_XL             0x2D
#define SENSORHUB1_REG        0x2E
#define SENSORHUB2_REG        0x2F
#define SENSORHUB3_REG        0x30
#define SENSORHUB4_REG        0x31
#define SENSORHUB5_REG        0x32
#define SENSORHUB6_REG        0x33
#define SENSORHUB7_REG        0x34
#define SENSORHUB8_REG        0x35
#define SENSORHUB9_REG        0x36
#define SENSORHUB10_REG       0x37
#define SENSORHUB11_REG       0x38
#define SENSORHUB12_REG       0x39
#define FIFO_STATUS1          0x3A
#define FIFO_STATUS2          0x3B
#define FIFO_STATUS3          0x3C
#define FIFO_STATUS4          0x3D
#define FIFO_DATA_OUT_L       0x3E
#define FIFO_DATA_OUT_H       0x3F
#define TIMESTAMP0_REG        0x40
#define TIMESTAMP1_REG        0x41
#define TIMESTAMP2_REG        0x42
#define STEP_COUNTER_L        0x4B
#define STEP_COUNTER_H        0x4C
#define FUNC_SR               0x53
#define TAP_CFG               0x58
#define TAP_THS_6D            0x59
#define INT_DUR2              0x5A
#define WAKE_UP_THS           0x5B
#define WAKE_UP_DUR           0x5C
#define FREE_FALL             0x5D
#define MD1_CFG               0x5E
#define MD2_CFG               0x5F

// init data
// enable timestamp etc etc
void NAP_LS6DS3_Init();
// Read full data when the threshold is full
void NAP_LS6DS3_FIFO_Read();
// Check if watermark sign is up
void NAP_LS6DS3_FIFO_Check();
