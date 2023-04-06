/*
 * Senales.c
 *
 *  Created on: 4 abr 2023
 *      Author: 2399d
 */

#include "Senales.h"
static uint16_t sine_wave[BUFFER_SIZE]={32768, 33575, 34382, 35188, 35992, 36795, 37595,
							38392, 39185, 39975, 40761, 41541, 42316, 43086, 43849, 44605,
							45354, 46096, 46829, 47554, 48270, 48977, 49674, 50360, 51036,
							51700, 52354, 52995, 53624, 54240, 54844, 55434, 56010, 56572,
							57119, 57652, 58170, 58672, 59159, 59629, 60083, 60521, 60942,
							61346, 61732, 62101, 62452, 62785, 63099, 63396, 63673, 63932,
							64172, 64393, 64595, 64777, 64940, 65084, 65208, 65312, 65396,
							65461, 65506, 65530, 65535, 65520, 65486, 65431, 65356, 65262,
							65148, 65015, 64861, 64689, 64496, 64285, 64055, 63805, 63537,
							63250, 62944, 62620, 62278, 61919, 61541, 61146, 60734, 60304,
							59858, 59396, 58917, 58423, 57913, 57388, 56847, 56293, 55723,
							55140, 54544, 53934, 53311, 52676, 52029, 51370, 50699, 50018,
							49326, 48625, 47913, 47193, 46464, 45726, 44981, 44228, 43468,
							42702, 41929, 41151, 40368, 39581, 38789, 37994, 37195, 36394,
							35590, 34785, 33979, 33172, 32364, 31557, 30751, 29946, 29142,
							28341, 27542, 26747, 25955, 25168, 24385, 23607, 22834, 22068,
							21308, 20555, 19810, 19072, 18343, 17623, 16911, 16210, 15518,
							14837, 14166, 13507, 12860, 12225, 11602, 10992, 10396, 9813,
							9243, 8689, 8148, 7623, 7113, 6619, 6140, 5678, 5232, 4802, 4390,
							3995, 3617, 3258, 2916, 2592, 2286, 1999, 1731, 1481, 1251, 1040,
							847, 675, 521, 388, 274, 180, 105, 50, 16, 1, 6, 30, 75, 140, 224,
							328, 452, 596, 759, 941, 1143, 1364, 1604, 1863, 2140, 2437, 2751,
							3084, 3435, 3804, 4190, 4594, 5015, 5453, 5907, 6377, 6864, 7366,
							7884, 8417, 8964, 9526, 10102, 10692, 11296, 11912, 12541, 13182,
							13836, 14500, 15176, 15862, 16559, 17266, 17982, 18707, 19440, 20182,
							20931, 21687, 22450, 23220, 23995, 24775, 25561, 26351, 27144, 27941,
							28741, 29544, 30348, 31154, 31961, 32768};

static uint16_t triangle_wave[BUFFER_SIZE]={0, 516, 1032, 1548, 2064, 2580, 3096, 3612, 4128, 4644,
							5160, 5676, 6192, 6708, 7224, 7740, 8257, 8773, 9289, 9805, 10321, 10837,
							11353, 11869, 12385, 12901, 13417, 13933, 14449, 14965, 15481, 15997, 16513,
							17029, 17545, 18061, 18577, 19093, 19609, 20125, 20641, 21157, 21673, 22189,
							22705, 23221, 23737, 24253, 24770, 25286, 25802, 26318, 26834, 27350, 27866,
							28382, 28898, 29414, 29930, 30446, 30962, 31478, 31994, 32510, 33026, 33542,
							34058, 34574, 35090, 35606, 36122, 36638, 37154, 37670, 38186, 38702, 39218,
							39734, 40250, 40766, 41283, 41799, 42315, 42831, 43347, 43863, 44379, 44895,
							45411, 45927, 46443, 46959, 47475, 47991, 48507, 49023, 49539, 50055, 50571,
							51087, 51603, 52119, 52635, 53151, 53667, 54183, 54699, 55215, 55731, 56247,
							56763, 57279, 57796, 58312, 58828, 59344, 59860, 60376, 60892, 61408, 61924,
							62440, 62956, 63472, 63988, 64504, 65020, 65535, 65535, 65020, 64504, 63988,
							63472, 62956, 62440, 61924, 61408, 60892, 60376, 59860, 59344, 58828, 58312,
							57796, 57279, 56763, 56247, 55731, 55215, 54699, 54183, 53667, 53151, 52635,
							52119, 51603, 51087, 50571, 50055, 49539, 49023, 48507, 47991, 47475, 46959,
							46443, 45927, 45411, 44895, 44379, 43863, 43347, 42831, 42315, 41799, 41283,
							40766, 40250, 39734, 39218, 38702, 38186, 37670, 37154, 36638, 36122, 35606,
							35090, 34574, 34058, 33542, 33026, 32510, 31994, 31478, 30962, 30446, 29930,
							29414, 28898, 28382, 27866, 27350, 26834, 26318, 25802, 25286, 24770, 24253,
							23737, 23221, 22705, 22189, 21673, 21157, 20641, 20125, 19609, 19093, 18577,
							18061, 17545, 17029, 16513, 15997, 15481, 14965, 14449, 13933, 13417, 12901,
							12385, 11869, 11353, 10837, 10321, 9805, 9289, 8773, 8257, 7740, 7224, 6708,
							6192, 5676, 5160, 4644, 4128, 3612, 3096, 2580, 2064, 1548, 1032, 516, 0};

static uint16_t sawtooth_wave[BUFFER_SIZE]= {0, 257, 514, 771, 1028, 1285, 1542, 1799, 2056, 2313, 2570,
							2827, 3084, 3341, 3598, 3855, 4112, 4369, 4626, 4883, 5140, 5397, 5654, 5911,
							6168, 6425, 6682, 6939, 7196, 7453, 7710, 7967, 8224, 8481, 8738, 8995, 9252,
							9509, 9766, 10023, 10280, 10537, 10794, 11051, 11308, 11565, 11822, 12079, 12336,
							12593, 12850, 13107, 13364, 13621, 13878, 14135, 14392, 14649, 14906, 15163, 15420,
							15677, 15934, 16191, 16448, 16705, 16962, 17219, 17476, 17733, 17990, 18247, 18504,
							18761, 19018, 19275, 19532, 19789, 20046, 20303, 20560, 20817, 21074, 21331, 21588,
							21845, 22102, 22359, 22616, 22873, 23130, 23387, 23644, 23901, 24158, 24415, 24672,
							24929, 25186, 25443, 25700, 25957, 26214, 26471, 26728, 26985, 27242, 27499, 27756,
							28013, 28270, 28527, 28784, 29041, 29298, 29555, 29812, 30069, 30326, 30583, 30840,
							31097, 31354, 31611, 31868, 32125, 32382, 32639, 32897, 33154, 33411, 33668, 33925,
							34182, 34439, 34696, 34953, 35210, 35467, 35724, 35981, 36238, 36495, 36752, 37009,
							37266, 37523, 37780, 38037, 38294, 38551, 38808, 39065, 39322, 39579, 39836, 40093,
							40350, 40607, 40864, 41121, 41378, 41635, 41892, 42149, 42406, 42663, 42920, 43177,
							43434, 43691, 43948, 44205, 44462, 44719, 44976, 45233, 45490, 45747, 46004, 46261,
							46518, 46775, 47032, 47289, 47546, 47803, 48060, 48317, 48574, 48831, 49088, 49345,
							49602, 49859, 50116, 50373, 50630, 50887, 51144, 51401, 51658, 51915, 52172, 52429,
							52686, 52943, 53200, 53457, 53714, 53971, 54228, 54485, 54742, 54999, 55256, 55513,
							55770, 56027, 56284, 56541, 56798, 57055, 57312, 57569, 57826, 58083, 58340, 58597,
							58854, 59111, 59368, 59625, 59882, 60139, 60396, 60653, 60910, 61167, 61424, 61681,
							61938, 62195, 62452, 62709, 62966, 63223, 63480, 63737, 63994, 64251, 64508, 64765,
							65022, 65279, 65535};

static signal_type_t current_signal =SIGNAL_SINE;
static uint32_t current_freq = DEFAULT_FREQ;


void Signal_NexType(void){
	current_signal = (current_signal + bit_1) % SIGNAL_COUNT;

}

void Signal_NexFreq(void){
	current_freq += FREQ_STEP;
	if(current_freq > MAX_FREQ){
		current_freq =DEFAULT_FREQ;
	}
}


uint16_t *Signals_GetActiveSignalBuffer(void){
	switch (current_signal){
		case SIGNAL_SINE:
			return sine_wave;
		case SIGNAL_TRIANGLE:
			return triangle_wave;
		case SIGNAL_SAWTOOTH:
			return sawtooth_wave;
		default:
			return 0;
	}

}
