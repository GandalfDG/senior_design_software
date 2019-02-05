/*
 * car_components.cpp
 *
 *  Created on: Feb 5, 2019
 *      Author: Jack
 */

#include "car_components.h"

Motor motor_l { kFTM_Chnl_0, kFTM_Chnl_1, kFTM_Chnl_4, kFTM_Chnl_5 };
Motor motor_r { kFTM_Chnl_2, kFTM_Chnl_3, kFTM_Chnl_6, kFTM_Chnl_7 };

Servo servo {kFTM_Chnl_0, 400, 2000};
