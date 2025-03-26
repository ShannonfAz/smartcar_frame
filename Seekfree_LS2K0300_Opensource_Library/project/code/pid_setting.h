#ifndef _pid_setting_h_
#define _pid_setting_h_
int pid_setting();
void pid_read_settings(unsigned int& motorl_speed,unsigned int& motorr_speed,float& servop,float& servod,float& motorp,float& motori);
#endif