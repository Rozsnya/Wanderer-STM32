#include "map.h"
#include "dma2d.h"

const uint32_t FLOOR_WIDTH = 27;
const uint32_t FLOOR_HEIGHT = 27;
const uint32_t FLOOR_DATA[] = { 0xff010001, 0xff080403, 0xff120f0c, 0xff120f0c,
		0xff120f0c, 0xff110f0c, 0xff11100b, 0xff0e0d09, 0xff110f0b, 0xff0e0d09,
		0xff110f0b, 0xff13120c, 0xff14120c, 0xff1f1f17, 0xff26241d, 0xff212018,
		0xff23211a, 0xff18180f, 0xff12120d, 0xff14140f, 0xff1b1b17, 0xff171813,
		0xff131110, 0xff1d1618, 0xff1e181b, 0xff090908, 0xff010101, 0xff090804,
		0xff534935, 0xff877957, 0xff7b6c45, 0xff887952, 0xff8f7d58, 0xff8a7751,
		0xff816e48, 0xff8b754d, 0xff806b3f, 0xff8f7a4f, 0xff907b4d, 0xff8d7749,
		0xff85713f, 0xffa08c5d, 0xffae9b69, 0xffaf9c67, 0xffa08f5a, 0xff9d8d59,
		0xff928256, 0xff8b7b54, 0xff757457, 0xff65634c, 0xff625d4a, 0xff6c6557,
		0xff444235, 0xff040403, 0xff222018, 0xff888061, 0xffa79660, 0xffa99255,
		0xff957a38, 0xffb49450, 0xffcfab64, 0xffd2ab62, 0xffcda453, 0xffd9b35b,
		0xffd9b35c, 0xffd3ad54, 0xffdcb75c, 0xffdbb75b, 0xfff0cd72, 0xfff7d16f,
		0xffefcc65, 0xfff0cd66, 0xfff1d06f, 0xffe1be65, 0xffcaa654, 0xffa9975a,
		0xff96874b, 0xff96874b, 0xff8b8150, 0xff797553, 0xff1c1c12, 0xff221f1c,
		0xff746b53, 0xff7b7050, 0xff857450, 0xff9f8852, 0xffa18438, 0xffbe9b40,
		0xffdcb44d, 0xffe7be54, 0xffddb64b, 0xffe4bf54, 0xffedc75b, 0xffdfbb4c,
		0xffd8b342, 0xfff8dc6d, 0xfff5d057, 0xfff3d254, 0xfff8d758, 0xfff5d760,
		0xffeac85d, 0xffd5b24e, 0xffc9a34f, 0xffd3b357, 0xffd6bb5d, 0xffc6b467,
		0xff8c8459, 0xff14120d, 0xff111211, 0xff3f3625, 0xff392e22, 0xff493a25,
		0xff8a7033, 0xffd5b760, 0xfff2cf6c, 0xffd6af49, 0xffdab34e, 0xffd2b046,
		0xffdcba51, 0xffd5b444, 0xffccaa37, 0xfff4d364, 0xfff9d967, 0xfff4d058,
		0xfff7d659, 0xfffbdc5f, 0xfff5d55f, 0xffd6b548, 0xffe9c564, 0xffe1ba56,
		0xffe1bd4b, 0xfff2d463, 0xffdfc974, 0xff877b4e, 0xff100f0a, 0xff0d0d0b,
		0xff685f45, 0xff947e50, 0xffc6ab6f, 0xffd6b660, 0xffe8c45c, 0xfff4cd60,
		0xffe8c059, 0xfff4cf6a, 0xffecca63, 0xffc2a235, 0xffd7b547, 0xfff1cf5f,
		0xfff9d967, 0xfffbdb6a, 0xfff8d561, 0xfffcde66, 0xfffee267, 0xfffddd6a,
		0xffedc95d, 0xffcea441, 0xffe2bc56, 0xfff4d263, 0xffedcc61, 0xffd3bb72,
		0xff837552, 0xff100f0b, 0xff0d0c08, 0xff82734b, 0xffc6a957, 0xffddba58,
		0xfff7d26d, 0xfffad367, 0xfff7d15e, 0xfff8d45c, 0xfff2cf5c, 0xfffad96f,
		0xfff4d364, 0xfff1d060, 0xfffde372, 0xfff6d762, 0xfff6d661, 0xfffedf6c,
		0xfffddd65, 0xfff7d55c, 0xfff9d762, 0xffffde72, 0xffdeb84f, 0xfff8d269,
		0xffe1bc4f, 0xffb5902d, 0xff907334, 0xff5c4d33, 0xff0a0907, 0xff211c12,
		0xff8f7a40, 0xffdfb950, 0xfffacf5b, 0xfff5c960, 0xffefc65e, 0xfff8d065,
		0xfff6d05d, 0xfff6d15c, 0xfff9d666, 0xfff5d15f, 0xfffdda67, 0xfffad661,
		0xfff8d760, 0xfffbd761, 0xfffcd968, 0xfff4d059, 0xfffbde66, 0xfffddd67,
		0xfff8d564, 0xfffad669, 0xfffedc68, 0xfff6d45e, 0xffeac762, 0xffcfb374,
		0xff827454, 0xff110f0c, 0xff483f2d, 0xffab8c4a, 0xffe5b74e, 0xfffacb5d,
		0xfff5c862, 0xffebc25e, 0xffedc661, 0xfff3cc61, 0xfff0ca59, 0xfffdd868,
		0xfff6d05f, 0xffefc956, 0xfff4ce5c, 0xfff7d15e, 0xfff5cf5a, 0xfff9d564,
		0xffedc955, 0xfff9d55e, 0xfff9d75f, 0xfffcd862, 0xfffcdb66, 0xfffde469,
		0xfff8d957, 0xfffddf68, 0xffe4cc7b, 0xff8a7e52, 0xff12120d, 0xff564a32,
		0xffbe9751, 0xffe1b04c, 0xffe4b74b, 0xfff1c95f, 0xfff1ce61, 0xffefc95d,
		0xfff5cc60, 0xfff0c75a, 0xfffad362, 0xfff1ca5a, 0xfff9d566, 0xfffdd96b,
		0xfffbd567, 0xfffcd86a, 0xfff9d564, 0xffecc954, 0xfff8d461, 0xfffedc64,
		0xffffe067, 0xfffbd85f, 0xfff4d05d, 0xfffada5a, 0xffebcf4b, 0xffdac567,
		0xff807446, 0xff0f0f0a, 0xff5b5235, 0xffbb954f, 0xffebbc5c, 0xfff1c45d,
		0xffe9c155, 0xfff2cf5f, 0xfff7d164, 0xfffad064, 0xfffbd468, 0xfff5ce61,
		0xffe5bd52, 0xffd5ab40, 0xffe2b852, 0xfff5ce66, 0xfff6cf62, 0xfff6d25f,
		0xfff7d361, 0xfffedc69, 0xfffddc64, 0xffffde66, 0xfffbda5f, 0xfff5d062,
		0xfff3d055, 0xfff3d254, 0xffe0c66e, 0xff7c6d44, 0xff0d0c08, 0xff4e452a,
		0xffb69650, 0xffebc160, 0xfff1c55d, 0xffeec25b, 0xffecc157, 0xfff1c55c,
		0xfff9cd64, 0xfffcd368, 0xfffad367, 0xffe7be59, 0xffbf952e, 0xffd1a843,
		0xffeac259, 0xfff3cc5d, 0xfff9d560, 0xfffcd964, 0xfffedb68, 0xfffedd69,
		0xfff5d25d, 0xfff7d35e, 0xfffddf72, 0xfff8d158, 0xfff9d35f, 0xffeacb7a,
		0xff88754e, 0xff0f0d09, 0xff5a5137, 0xffb59551, 0xffe3b858, 0xffe4b853,
		0xffebbf59, 0xffefc35c, 0xfff3c75f, 0xffface65, 0xffe6be4d, 0xfff5ce5e,
		0xfff9d36a, 0xffecc35d, 0xffeac25b, 0xffefc85a, 0xfffcd764, 0xfff6d35f,
		0xfffbd867, 0xfffcdc6a, 0xffeec957, 0xfffdde6e, 0xfff7d464, 0xffefcb60,
		0xfff3d15d, 0xffe0b843, 0xffcbac58, 0xff8e7a51, 0xff12100c, 0xff4e452d,
		0xffae8d4a, 0xffe4b75a, 0xffcd9f3a, 0xffddb04a, 0xfff4c861, 0xfff2c65c,
		0xffe8bd52, 0xfff2c95a, 0xfffad564, 0xffeeca5c, 0xffebc457, 0xfffad366,
		0xfffad361, 0xfff8d55f, 0xfff9d564, 0xfff8d564, 0xffeac654, 0xfffbd86a,
		0xffe8c553, 0xffdab544, 0xffc0982e, 0xffd5ab36, 0xfff3ca5c, 0xffccad5a,
		0xff766339, 0xff0c0a05, 0xff504832, 0xffa78542, 0xffd9ab51, 0xffd7a947,
		0xffd9ac48, 0xfff0c35d, 0xfff8cc64, 0xfff0c559, 0xffedc456, 0xffe5bf50,
		0xffd8b142, 0xfff5ce61, 0xfff4cd5c, 0xfff5cf5a, 0xfff7d25a, 0xfff3d05e,
		0xffe8c753, 0xffdfbb4a, 0xffe6c154, 0xffd4af3f, 0xffd7b245, 0xfff1ca66,
		0xffebc251, 0xfff7ce61, 0xffd2b363, 0xff88744d, 0xff110f0b, 0xff554b38,
		0xffab8845, 0xffd6a84f, 0xffd1a245, 0xffe1b352, 0xffe3b752, 0xfff1c45c,
		0xfff3c85b, 0xfff4cb62, 0xffeac25a, 0xfff6ce63, 0xfff0c95a, 0xfff6cf5e,
		0xfff8d25d, 0xfffbd764, 0xfff6d260, 0xfff9d566, 0xfffcda6e, 0xffcea93a,
		0xffeac35f, 0xffecc560, 0xffe6bf58, 0xffecc352, 0xffeec557, 0xffcfaf60,
		0xff887550, 0xff130f0c, 0xff473d2c, 0xffa17f3e, 0xffd3a54a, 0xffe1b353,
		0xffebbd5d, 0xfff2c460, 0xfff0c35b, 0xfff5c95e, 0xfff1c55d, 0xffe9be58,
		0xffe7bd53, 0xfff8d065, 0xfff9d264, 0xfff4cd5d, 0xfff6ce5e, 0xfff8d363,
		0xfff7d265, 0xffe7c154, 0xffe3bb51, 0xffe2ba53, 0xffddb44f, 0xffe5c054,
		0xffecc652, 0xffd8b242, 0xffc3a45a, 0xff715f3d, 0xff161411, 0xff3d3226,
		0xff9d8143, 0xffc89d3d, 0xfff3c460, 0xfff0c15c, 0xffe8b953, 0xfff1c25a,
		0xffeabd53, 0xfff2c45d, 0xffeec15a, 0xffefc35b, 0xfff8cd63, 0xffedc658,
		0xfff4cc5d, 0xfffad666, 0xfff0c658, 0xfff8ce62, 0xffdeb445, 0xfff0c45b,
		0xffdcb047, 0xffe0b44d, 0xffddb547, 0xffe9c554, 0xffe4c460, 0xffa48948,
		0xff6a5c40, 0xff0d0c0a, 0xff423a2b, 0xff8d7037, 0xffddae56, 0xffe9ba56,
		0xffe6b752, 0xfff1c25c, 0xfff0c15b, 0xffeabc54, 0xfff1c45b, 0xfffacc64,
		0xfff3c75d, 0xfff7cd61, 0xffecc557, 0xfff1ca5a, 0xfff5d160, 0xffecc053,
		0xfff1c55a, 0xffe7bc50, 0xffe1b649, 0xffe3b74e, 0xffdaae43, 0xffe2ba4f,
		0xffe1bc4d, 0xffddba57, 0xff846823, 0xff716347, 0xff100f0b, 0xff3f3627,
		0xff896837, 0xffd1a44c, 0xffe4b552, 0xffe8b955, 0xffdfb14a, 0xffebbc55,
		0xffedbf58, 0xfff4c65e, 0xfff1c459, 0xfff2c75c, 0xfff4c95e, 0xffefc85b,
		0xfff3cc5e, 0xfff0cb5d, 0xfff3c85d, 0xffebbf54, 0xfff1c65d, 0xfff5c95f,
		0xffeabe54, 0xffecc157, 0xffdab248, 0xffdcb546, 0xffc09c36, 0xffc7ab6a,
		0xff857557, 0xff151410, 0xff362d20, 0xff8d6b3d, 0xffe1b25c, 0xffe6b656,
		0xffeabc59, 0xfff2c360, 0xffeebf5a, 0xffedbe59, 0xffe0b24a, 0xfff2c45b,
		0xfff3c75f, 0xfff8cc67, 0xfff2c962, 0xfff0c762, 0xfff0ca63, 0xffface67,
		0xfff2c75e, 0xfff0c45a, 0xfffed26a, 0xfff3c85e, 0xfff4ca5e, 0xffecc260,
		0xffd4ab3f, 0xffdeb954, 0xffd5b875, 0xff715f41, 0xff0a0704, 0xff291f16,
		0xff81612f, 0xffd5a651, 0xffe9b959, 0xffe7b756, 0xffe8b957, 0xffeabb58,
		0xffe8b954, 0xffeabb57, 0xfff5c665, 0xfff0c160, 0xfff2c465, 0xffc69c36,
		0xffbc912a, 0xffe5bd5d, 0xffefc35c, 0xffe3b64c, 0xffedc157, 0xfff5c95f,
		0xfff6cb5e, 0xfff7cc60, 0xffe5b758, 0xffe4ba50, 0xffcca63e, 0xffcaac65,
		0xff7b6948, 0xff0d0b07, 0xff362a1f, 0xff9c7e4a, 0xffb78a32, 0xffe1b253,
		0xffe1b253, 0xffebbd5e, 0xffe7b856, 0xffecbd5a, 0xffe5b653, 0xffe2b253,
		0xffe3b456, 0xffd5a84a, 0xffc99e42, 0xffd7ad53, 0xffc59c3e, 0xffe3b650,
		0xffe8bb54, 0xfff4c860, 0xfff8ce62, 0xfff9ce61, 0xffeec254, 0xfff4c668,
		0xffd3a73c, 0xffd4ab45, 0xffc2a35b, 0xff786542, 0xff0e0b08, 0xff3e2e1d,
		0xff927939, 0xffcb9f56, 0xffa87a2f, 0xffb48f40, 0xffcaa754, 0xffd8b457,
		0xffd8ab47, 0xffe6b853, 0xffd7a947, 0xfff5c86b, 0xffd3a947, 0xffc49a3b,
		0xffe0b85e, 0xffe1b95f, 0xffc3993b, 0xffd0a545, 0xffebbf5d, 0xffe6b851,
		0xfff5c85e, 0xfff9ca60, 0xfff6c35a, 0xffe7b64b, 0xffd8b04d, 0xffb49650,
		0xff5b4828, 0xff0d0809, 0xff34291f, 0xff847042, 0xff936e39, 0xff987340,
		0xff957640, 0xff886d38, 0xffaa8843, 0xffcfa654, 0xffdeb152, 0xffe8b755,
		0xffe1b354, 0xfff1c369, 0xffac8122, 0xffd2a954, 0xffb9913f, 0xffd3ad64,
		0xffbf9a4c, 0xffc39e4d, 0xffd4ad58, 0xffd9b058, 0xffe1b95d, 0xffe4bf63,
		0xffdeba62, 0xffb99c4e, 0xffa28d57, 0xff5d5336, 0xff090805, 0xff0d0a07,
		0xff574937, 0xff655438, 0xff594934, 0xff312417, 0xff3b302a, 0xff6d5839,
		0xffa18655, 0xffbc9b58, 0xffc1994d, 0xffbc9852, 0xffb59453, 0xffa78a50,
		0xff846a31, 0xff8e7545, 0xff826d43, 0xff8f784e, 0xff897245, 0xff8d7544,
		0xff8c7440, 0xff9e8852, 0xff97884c, 0xff95844e, 0xff8c7c52, 0xff615439,
		0xff221f15, 0xff000100, 0xff000001, 0xff080605, 0xff100f0c, 0xff050402,
		0xff030307, 0xff1a171a, 0xff2d2824, 0xff49402c, 0xff5d5031, 0xff6a5d3c,
		0xff5e5337, 0xff453e28, 0xff2e281c, 0xff221d14, 0xff18140d, 0xff130f0b,
		0xff17120d, 0xff15110b, 0xff14100c, 0xff100d07, 0xff15130d, 0xff17130b,
		0xff1b150d, 0xff17130f, 0xff0d0a08, 0xff020102, 0xff000000, };

const uint32_t WALL_WIDTH = 27;
const uint32_t WALL_HEIGHT = 27;
const uint32_t WALL_DATA[] = { 0xff000000, 0xff010202, 0xff050606, 0xff050707,
		0xff080a0a, 0xff090d0d, 0xff0c0e0e, 0xff080a0a, 0xff0d0e0f, 0xff0c0d0d,
		0xff0f1012, 0xff191b1e, 0xff1e2123, 0xff1b1e21, 0xff0f1014, 0xff0a0b0c,
		0xff0b0d0d, 0xff0a0d0c, 0xff060808, 0xff020403, 0xff070909, 0xff070909,
		0xff000101, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
		0xff1c2122, 0xff374141, 0xff354140, 0xff3f4f4f, 0xff425353, 0xff425051,
		0xff364044, 0xff50595f, 0xff495157, 0xff3e454c, 0xff414950, 0xff51575f,
		0xff4d545b, 0xff50555e, 0xff474e56, 0xff424e52, 0xff445656, 0xff364641,
		0xff192721, 0xff3f4d49, 0xff3d4a49, 0xff181e21, 0xff22252a, 0xff272c2c,
		0xff0f1312, 0xff000000, 0xff000000, 0xff273032, 0xff485355, 0xff475558,
		0xff4f5f62, 0xff405153, 0xff0e1114, 0xff48545b, 0xff39434e, 0xff313742,
		0xff3b444f, 0xff3e4753, 0xff343d49, 0xff47515c, 0xff454e5a, 0xff4a525e,
		0xff3e4b54, 0xff4b6162, 0xff4d5f5b, 0xff354841, 0xff4c5f59, 0xff101313,
		0xff404a50, 0xff555c65, 0xff4a5355, 0xff313d38, 0xff060807, 0xff020303,
		0xff212b2d, 0xff445357, 0xff536468, 0xff5d6b70, 0xff0b161c, 0xff36444a,
		0xff424b56, 0xff414755, 0xff525567, 0xff4f5364, 0xff535668, 0xff4a4d5f,
		0xff4a4d5f, 0xff606475, 0xff626576, 0xff5d6873, 0xff3e5355, 0xff1e322e,
		0xff23352e, 0xff030705, 0xff404e50, 0xff4f5963, 0xff3e4956, 0xff5a686b,
		0xff576861, 0xff0c0f0d, 0xff030404, 0xff172426, 0xff3c4c4f, 0xff5a6d71,
		0xff3e484c, 0xff2a3038, 0xff505762, 0xff393e4e, 0xff4c4d60, 0xff4e5065,
		0xff504e64, 0xff48475c, 0xff58566b, 0xff59596e, 0xff66667b, 0xff67667b,
		0xff646a79, 0xff617076, 0xff465554, 0xff0f1d18, 0xff2a3a36, 0xff233033,
		0xff515965, 0xff5a6673, 0xff647376, 0xff576a63, 0xff0b0f0e, 0xff040404,
		0xff14201f, 0xff455554, 0xff455856, 0xff273335, 0xff474d55, 0xff565c69,
		0xff41465a, 0xff393d52, 0xff42475b, 0xff4b4d5f, 0xff5f5c70, 0xff68687e,
		0xff66687f, 0xff686b7f, 0xff636777, 0xff5c6671, 0xff58666c, 0xff1f2e34,
		0xff4c5a5e, 0xff313f43, 0xff3c4b50, 0xff26323a, 0xff5d666e, 0xff647878,
		0xff4a5e59, 0xff0a0d0c, 0xff050707, 0xff1c2626, 0xff40504e, 0xff3e4f4d,
		0xff25292d, 0xff464d57, 0xff575c6a, 0xff5c6074, 0xff686d82, 0xff676b7d,
		0xff686a7b, 0xff68677a, 0xff686a7f, 0xff64677d, 0xff63687a, 0xff636876,
		0xff636f77, 0xff414f55, 0xff3d4a50, 0xff57646a, 0xff344348, 0xff4a575e,
		0xff4e5760, 0xff1c252d, 0xff4f6364, 0xff4c5f5b, 0xff090c0b, 0xff080909,
		0xff222a2c, 0xff414e51, 0xff142426, 0xff49545b, 0xff494f5b, 0xff565a6c,
		0xff54596d, 0xff5e6277, 0xff5d6274, 0xff626576, 0xff5b5c6f, 0xff65677d,
		0xff65687c, 0xff626a79, 0xff656f79, 0xff5b656d, 0xff26313b, 0xff535e66,
		0xff555f68, 0xff5a656d, 0xff59636c, 0xff575f68, 0xff545c63, 0xff1c3031,
		0xff354a46, 0xff0a0d0c, 0xff020304, 0xff0b1114, 0xff19242a, 0xff3b484f,
		0xff444d58, 0xff525766, 0xff666a7d, 0xff5a5e73, 0xff5d6176, 0xff5e6274,
		0xff636778, 0xff606476, 0xff5c6176, 0xff636a7d, 0xff57606d, 0xff657379,
		0xff3d484f, 0xff464d59, 0xff575e69, 0xff555b67, 0xff5e6570, 0xff656d77,
		0xff5c616c, 0xff636c73, 0xff4b5f60, 0xff2b3f3c, 0xff020504, 0xff090c0e,
		0xff22272c, 0xff495057, 0xff404b55, 0xff484f5d, 0xff525769, 0xff66697f,
		0xff61647c, 0xff606478, 0xff5d6174, 0xff65687a, 0xff686b7f, 0xff5f6479,
		0xff666e7f, 0xff626e78, 0xff617074, 0xff3b464b, 0xff494e5a, 0xff5d636f,
		0xff676d79, 0xff6a707b, 0xff636975, 0xff656a75, 0xff656c74, 0xff586c6c,
		0xff3d504d, 0xff090b0b, 0xff0a0e0f, 0xff262c33, 0xff414750, 0xff4c525f,
		0xff494e5f, 0xff626679, 0xff676980, 0xff5e6179, 0xff62667b, 0xff5d6273,
		0xff626778, 0xff656d81, 0xff626a7e, 0xff606a79, 0xff65727b, 0xff4e6161,
		0xff384549, 0xff565966, 0xff616572, 0xff6a6d7a, 0xff757885, 0xff6b6d7b,
		0xff60636f, 0xff535c64, 0xff516666, 0xff4f625e, 0xff0b0e0d, 0xff0d100f,
		0xff272d2f, 0xff393f49, 0xff48505e, 0xff535367, 0xff6e6a82, 0xff6e6b83,
		0xff63667c, 0xff64677d, 0xff63667c, 0xff626a7e, 0xff5e6b7b, 0xff606d7a,
		0xff5f6e76, 0xff657678, 0xff263b37, 0xff4f5f61, 0xff5b6972, 0xff6b767f,
		0xff606a74, 0xff656d76, 0xff676d76, 0xff626a71, 0xff5a6568, 0xff526062,
		0xff526162, 0xff0f1111, 0xff111615, 0xff2a2f30, 0xff414751, 0xff4a5261,
		0xff4f5265, 0xff6b6d81, 0xff6a6f81, 0xff5a5f70, 0xff636c7b, 0xff636b79,
		0xff646e7c, 0xff697580, 0xff67747c, 0xff606d72, 0xff3f4f51, 0xff41514f,
		0xff576665, 0xff556464, 0xff596969, 0xff566766, 0xff5c6c6b, 0xff5a696b,
		0xff465456, 0xff546062, 0xff525f61, 0xff515e60, 0xff0a0d0e, 0xff121716,
		0xff2a2f30, 0xff40474d, 0xff48515e, 0xff545f6d, 0xff5e6876, 0xff55636d,
		0xff59686f, 0xff627376, 0xff617175, 0xff6c7c7f, 0xff526264, 0xff313c3e,
		0xff2e3e40, 0xff2c3d3f, 0xff344345, 0xff233432, 0xff293934, 0xff253732,
		0xff22362f, 0xff253833, 0xff243430, 0xff1c2c29, 0xff222d2d, 0xff293132,
		0xff202e2e, 0xff040607, 0xff171b19, 0xff2a3030, 0xff3d454a, 0xff47525b,
		0xff5d6d75, 0xff5b6d73, 0xff58686c, 0xff607174, 0xff667878, 0xff556866,
		0xff1c2829, 0xff151f21, 0xff3f4d4e, 0xff4e5b5d, 0xff535e64, 0xff465157,
		0xff434e54, 0xff4c585c, 0xff4e5a5e, 0xff404e51, 0xff3e4d4e, 0xff344243,
		0xff404f4e, 0xff323f3e, 0xff283433, 0xff2f3e3d, 0xff090b0b, 0xff141a16,
		0xff232927, 0xff4b5455, 0xff536063, 0xff586a6c, 0xff576c6c, 0xff536464,
		0xff344646, 0xff0e1c1f, 0xff0d1618, 0xff3c4a4f, 0xff505b61, 0xff4b565d,
		0xff576169, 0xff5b646e, 0xff4e5861, 0xff434e59, 0xff4b5560, 0xff4c5661,
		0xff424950, 0xff303539, 0xff2f3434, 0xff454a4a, 0xff576461, 0xff5c6a67,
		0xff495955, 0xff0b0e0d, 0xff0b110d, 0xff171d19, 0xff222b29, 0xff4b5759,
		0xff24302f, 0xff1c2e2a, 0xff202c2b, 0xff313a3d, 0xff444d56, 0xff4e535f,
		0xff565a68, 0xff515665, 0xff5e636f, 0xff636976, 0xff6e747f, 0xff646a75,
		0xff606875, 0xff58626f, 0xff444c53, 0xff292c2d, 0xff1f1c17, 0xff514b40,
		0xff56544a, 0xff5a6763, 0xff6b7976, 0xff5a6865, 0xff0d0f0f, 0xff070a09,
		0xff2c3533, 0xff445150, 0xff243333, 0xff3f4e4f, 0xff3e4b4d, 0xff434a54,
		0xff545965, 0xff575a67, 0xff5a5d6a, 0xff636774, 0xff596270, 0xff6a6e7f,
		0xff6c7080, 0xff676a78, 0xff696e78, 0xff616973, 0xff606872, 0xff3f4145,
		0xff161310, 0xff716355, 0xffaa957d, 0xff746551, 0xff59655f, 0xff687d77,
		0xff5b6f68, 0xff0e100f, 0xff161b1b, 0xff444e4d, 0xff233231, 0xff384646,
		0xff252b2d, 0xff596269, 0xff656b77, 0xff5c616e, 0xff5d606e, 0xff585b68,
		0xff60636a, 0xff656971, 0xff636672, 0xff5f6571, 0xff5f6671, 0xff4a515a,
		0xff515c64, 0xff58606a, 0xff4e4e53, 0xff3c362f, 0xff867969, 0xffaa967f,
		0xff5b4f3a, 0xff616c65, 0xff6c857d, 0xff5d736b, 0xff101211, 0xff1b1f1f,
		0xff545c5e, 0xff3d4a4d, 0xff243436, 0xff122022, 0xff465256, 0xff666b75,
		0xff6c707d, 0xff636673, 0xff454954, 0xff303033, 0xff4a4a49, 0xff6c6f74,
		0xff545962, 0xff4e5962, 0xff5c686f, 0xff606b72, 0xff5d646b, 0xff55595c,
		0xff484b47, 0xff403f37, 0xff6f6c5d, 0xff5c5b4f, 0xff717d77, 0xff6c847d,
		0xff697e77, 0xff111613, 0xff0f1313, 0xff4b5356, 0xff465258, 0xff49585d,
		0xff1b2325, 0xff2d393b, 0xff5a616b, 0xff646874, 0xff535762, 0xff34383f,
		0xff4f4f4f, 0xff64635f, 0xff5e6162, 0xff596066, 0xff59656c, 0xff59696e,
		0xff5b696c, 0xff565e62, 0xff656c6f, 0xff505858, 0xff444d48, 0xff485049,
		0xff747c75, 0xff808d88, 0xff667f77, 0xff61776f, 0xff0e1110, 0xff0d0d0e,
		0xff475054, 0xff404b51, 0xff54616b, 0xff3a484a, 0xff142023, 0xff353c44,
		0xff565b66, 0xff5f636e, 0xff4a4f57, 0xff626464, 0xff6c6e6c, 0xff5a5c60,
		0xff696f75, 0xff4f5960, 0xff5a6669, 0xff5c686b, 0xff565f60, 0xff5f6767,
		0xff5f6a67, 0xff5e6a67, 0xff616e6b, 0xff727c78, 0xff74807a, 0xff637d74,
		0xff536961, 0xff0c0f0e, 0xff0b0d0d, 0xff4a5258, 0xff47525b, 0xff4e5b66,
		0xff4e5d5e, 0xff091011, 0xff424950, 0xff414750, 0xff515660, 0xff61666d,
		0xff505558, 0xff60676b, 0xff82868f, 0xff757984, 0xff666b74, 0xff62686c,
		0xff565d5f, 0xff56605d, 0xff545c5a, 0xff636c68, 0xff6f7873, 0xff6d7570,
		0xff686e6a, 0xff75817b, 0xff6d857d, 0xff536a62, 0xff0b0e0c, 0xff0d0d0e,
		0xff474e53, 0xff424c56, 0xff525d67, 0xff475458, 0xff2e393c, 0xff242e36,
		0xff4a525b, 0xff4d555d, 0xff5d636b, 0xff667176, 0xff616e72, 0xff657176,
		0xff7a858b, 0xff778185, 0xff687374, 0xff606e6c, 0xff707f79, 0xff6f7d78,
		0xff72807a, 0xff5f6d67, 0xff57655e, 0xff677770, 0xff50685f, 0xff546c64,
		0xff44544e, 0xff070a09, 0xff0a0a0b, 0xff42474c, 0xff495158, 0xff5e686f,
		0xff5a656b, 0xff556165, 0xff070c0e, 0xff475457, 0xff475256, 0xff586468,
		0xff5d696d, 0xff5d6d6f, 0xff667576, 0xff5a696a, 0xff707f7e, 0xff758582,
		0xff71827f, 0xff697c77, 0xff6c7e7a, 0xff657772, 0xff647670, 0xff546662,
		0xff58706a, 0xff45665d, 0xff485752, 0xff161e1a, 0xff020302, 0xff020303,
		0xff272c2f, 0xff464f54, 0xff556066, 0xff5a6869, 0xff546260, 0xff263330,
		0xff253331, 0xff475452, 0xff5f6d6a, 0xff5d6c6c, 0xff5a6a6b, 0xff4f6060,
		0xff455657, 0xff435553, 0xff576964, 0xff50645f, 0xff425651, 0xff465b56,
		0xff485c57, 0xff3f534e, 0xff445854, 0xff49615b, 0xff1a2b27, 0xff1b2321,
		0xff202322, 0xff030303, 0xff000000, 0xff030303, 0xff0d1113, 0xff0c0f10,
		0xff0e1010, 0xff0e1411, 0xff0b120f, 0xff020503, 0xff0c1411, 0xff0f1613,
		0xff0e1111, 0xff0c0f0f, 0xff0a0e0e, 0xff060a08, 0xff050907, 0xff080c0b,
		0xff080b0a, 0xff070e0a, 0xff060b09, 0xff060b09, 0xff040907, 0xff07120f,
		0xff060a09, 0xff000100, 0xff0a0b0b, 0xff010101, 0xff000000, };


int map[10][10] = {{0,0,0,1,0,1,0,0,0,0},
	               {0,0,0,1,0,1,0,1,1,0},
	 	           {0,1,1,1,0,1,0,1,1,0},
	  	           {0,0,0,0,0,1,0,0,0,0},
	  	           {1,1,1,1,0,1,1,1,1,0},
	  	           {0,1,0,1,0,0,0,0,1,0},
	  	           {0,1,0,1,0,1,1,0,1,0},
	  	           {0,0,0,0,0,1,1,0,1,0},
	  	           {0,1,1,1,0,0,0,0,1,0},
	  	           {0,0,0,1,0,1,1,0,0,0},
		          };

void map_init(){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(map[i][j] == 0){
				DMA2D_DrawImage((uint32_t)FLOOR_DATA, 105 + j * 27, 1 + i * 27, 27, 27);
			} else {
				DMA2D_DrawImage((uint32_t)WALL_DATA, 105 + j * 27, 1 + i * 27, 27, 27);
			}
		}
	}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawLine(105, 0, 375, 0);
	BSP_LCD_DrawLine(375, 0, 375, 271);
	BSP_LCD_DrawLine(105, 0, 105, 271);
	BSP_LCD_DrawLine(105, 271, 375, 271);
}
