/*
 * Sound samples available on the drum trigger.
 */
 
 // clap array
 // tamborine array
 #ifndef SOUNDSAMPLES_H
 #define SOUNDSAMPLES_H
static const unsigned short Bassoon64[64]={
1068, 1169, 1175, 1161, 1130, 1113, 1102, 1076, 1032, 985, 963, 987, 1082, 1343, 1737, 1863,
1575, 1031, 538, 309, 330, 472, 626, 807, 1038, 1270, 1420, 1461, 1375, 1201, 1005, 819, 658,
532, 496, 594, 804, 1055, 1248, 1323, 1233, 1049, 895, 826, 826, 850, 862, 861, 899, 961, 1006,
1023, 1046, 1092, 1177, 1224, 1186, 1133, 1098, 1102, 1109, 1076, 1027, 1003};


    static int* soundToPlay;
    static int* soundArray[7] = { 0, 0, 0, 0, 0, 0, 0};
extern int changeFlag;
extern int menuIndex;
    
#endif

    