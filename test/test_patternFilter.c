#include "unity.h"
#include "patternFilter.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/*
 *        1   2   3   4   5   6   7   8   9   10                                                      9   10
 *        11  12  13  14  15  16  17  18  19  20                                                      19  20
 *        21  22  23  24  25  26  27  28  29  30                                                      29  30
 *        31  32  33  34  35  36  37  38  39  40                                                      39  40
 *        41  42  43  44  45  46  47  48  49  50      =============>                                  49  50         9,10,19,20,29,30,39,40,49,50,59,60,69,70,79,80,89,90,91,92,93,94,95,96,97,98,99,100 
 *        51  52  53  54  55  56  57  58  59  60                                                      59  60
 *        61  62  63  64  65  66  67  68  69  70                                                      69  70
 *        71  72  73  74  75  76  77  78  79  80                                                      79  80 
 *        81  82  83  84  85  86  87  88  89  90                                                      89  90
 *        91  92  93  94  95  96  97  98  99  100                     91  92  93  94  95  96  97  98  99  100
 *
 *
 */
void test_filter_left_top_pattern(void){
	int dataMatrix [10][10]   = {{1,2,3,4,5,6,7,8,9,10},
                      {11,12,13,14,15,16,17,18,19,20},
                      {21,22,23,24,25,26,27,28,29,30},
                      {31,32,33,34,35,36,37,38,39,40},
                      {41,42,43,44,45,46,47,48,49,50},
                      {51,52,53,54,55,56,57,58,59,60},
                      {61,62,63,64,65,66,67,68,69,70},
                      {71,72,73,74,75,76,77,78,79,80},
                      {81,82,83,84,85,86,87,88,89,90},
                      {91,92,93,94,95,96,97,98,99,100}};
                      
 leftTopFilter((int*)dataMatrix, 10, 10);   
}

/*
 *        1   2   3   4   5   6   7   8   9   10                      1   2
 *        11  12  13  14  15  16  17  18  19  20                      11  12
 *        21  22  23  24  25  26  27  28  29  30                      21  22
 *        31  32  33  34  35  36  37  38  39  40                      31  32
 *        41  42  43  44  45  46  47  48  49  50      =============>  41  42                                    1,2,11,12,21,22,31,32,41,42,51,52,61,62,71,72,81,82,91,92,93,94,95,96,97,98,99,100 
 *        51  52  53  54  55  56  57  58  59  60                      51  52
 *        61  62  63  64  65  66  67  68  69  70                      61  62
 *        71  72  73  74  75  76  77  78  79  80                      71  72
 *        81  82  83  84  85  86  87  88  89  90                      81  82
 *        91  92  93  94  95  96  97  98  99  100                     91  92  93  94  95  96  97  98  99  100
 *
 *
 */
void test_filter_right_top_pattern(void){
	int dataMatrix [10][10]   = {{1,2,3,4,5,6,7,8,9,10},
                      {11,12,13,14,15,16,17,18,19,20},
                      {21,22,23,24,25,26,27,28,29,30},
                      {31,32,33,34,35,36,37,38,39,40},
                      {41,42,43,44,45,46,47,48,49,50},
                      {51,52,53,54,55,56,57,58,59,60},
                      {61,62,63,64,65,66,67,68,69,70},
                      {71,72,73,74,75,76,77,78,79,80},
                      {81,82,83,84,85,86,87,88,89,90},
                      {91,92,93,94,95,96,97,98,99,100}};
                      
 rightTopFilter((int*)dataMatrix, 10, 10);   
}

/*
 *        1   2   3   4   5   6   7   8   9   10                      1   2   3   4   5   6   7   8   9   10
 *        11  12  13  14  15  16  17  18  19  20                      11  12  13  14  15  16  17  18  19  20
 *        21  22  23  24  25  26  27  28  29  30                                                      29  30
 *        31  32  33  34  35  36  37  38  39  40                                                      39  40
 *        41  42  43  44  45  46  47  48  49  50      =============>                                  49  50         1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,29,30,39,40,49,50,59,60,69,70,79,80,89,90,99,100 
 *        51  52  53  54  55  56  57  58  59  60                                                      59  60
 *        61  62  63  64  65  66  67  68  69  70                                                      69  70
 *        71  72  73  74  75  76  77  78  79  80                                                      79  80 
 *        81  82  83  84  85  86  87  88  89  90                                                      89  90
 *        91  92  93  94  95  96  97  98  99  100                                                     99  100
 *
 *
 */
void test_filter_left_bottom_pattern(void){
	int dataMatrix [10][10]   = {{1,2,3,4,5,6,7,8,9,10},
                      {11,12,13,14,15,16,17,18,19,20},
                      {21,22,23,24,25,26,27,28,29,30},
                      {31,32,33,34,35,36,37,38,39,40},
                      {41,42,43,44,45,46,47,48,49,50},
                      {51,52,53,54,55,56,57,58,59,60},
                      {61,62,63,64,65,66,67,68,69,70},
                      {71,72,73,74,75,76,77,78,79,80},
                      {81,82,83,84,85,86,87,88,89,90},
                      {91,92,93,94,95,96,97,98,99,100}};
                      
 leftBottomFilter((int*)dataMatrix, 10, 10);
 darkModuleFilter((int*)dataMatrix, 10, 10);
}

/*
 *        1   2   3   4   5   6   7   8   9   10                      1   2   3   4   5   6       8   9   10
 *        11  12  13  14  15  16  17  18  19  20                      11  12  13  14  15  16      18  19  20
 *        21  22  23  24  25  26  27  28  29  30                      21  22  23  24  25  26      28  29  30
 *        31  32  33  34  35  36  37  38  39  40                      31  32  33  34  35  36      38  39  40
 *        41  42  43  44  45  46  47  48  49  50      =============>  41  42  43  44  45  46      48  49  50         1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,29,30,39,40,49,50,59,60,69,70,79,80,89,90,99,100 
 *        51  52  53  54  55  56  57  58  59  60                      51  52  53  54  55  56      58  59  60
 *        61  62  63  64  65  66  67  68  69  70                      
 *        71  72  73  74  75  76  77  78  79  80                      71  72  73  74  75  76      78  79  80
 *        81  82  83  84  85  86  87  88  89  90                      81  82  83  84  85  86      88  89  90
 *        91  92  93  94  95  96  97  98  99  100                     91  92  93  94  95  96      98  99  100
 *
 *
 */
void test_filter_timming_pattern(void){
	int dataMatrix [10][10]   = {{1,2,3,4,5,6,7,8,9,10},
                      {11,12,13,14,15,16,17,18,19,20},
                      {21,22,23,24,25,26,27,28,29,30},
                      {31,32,33,34,35,36,37,38,39,40},
                      {41,42,43,44,45,46,47,48,49,50},
                      {51,52,53,54,55,56,57,58,59,60},
                      {61,62,63,64,65,66,67,68,69,70},
                      {71,72,73,74,75,76,77,78,79,80},
                      {81,82,83,84,85,86,87,88,89,90},
                      {91,92,93,94,95,96,97,98,99,100}};
                      
 timingPatternFilter((int*)dataMatrix, 10, 10);   
}