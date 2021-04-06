/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

#include "scenario.h"
#include <string.h>
#include <direct.h>
#include <fstream>
#include "files.h"
#include <list>
#include <experimental/filesystem>
#include "keyboard.h"

DWORD	vehUpdateTime;
DWORD	pedUpdateTime;
using namespace std;
namespace fs = std::experimental::filesystem;

std::vector<Hash> hashes = {
	3462393972,
	2864127842,
	2825402133,
	351016938,
	1457690978,
	4244282910,
	1682622302,
	402729631,
	3630914197,
	802685111,
	1794449327,
	1318032802,
	307287994,
	2971380566,
	111281960,
	3283429734,
	882848737,
	3268439891,
	2506301981,
	3549666813,
	113504370,
	1126154828,
	808859815,
	3188223741,
	2688103263,
	1004114196,
	532905404,
	1699403886,
	2638072698,
	1674107025,
	4206136267,
	3050275044,
	951767867,
	1388848350,
	1090617681,
	379310561,
	3725461865,
	2962707003,
	3454621138,
	1951946145,
	4079145784,
	1347814329,
	2359345766,
	1224306523,
	1640504453,
	3134700416,
	1204772502,
	3439295882,
	1039800368,
	2775443222,
	3349113128,
	1146800212,
	1546450936,
	549978415,
	920595805,
	664399832,
	826475330,
	2928082356,
	3083210802,
	4121954205,
	70821038,
	1371553700,
	1755064960,
	1165780219,
	331645324,
	793439294,
	2111372120,
	813893651,
	343259175,
	2185745201,
	2549481101,
	2780469782,
	429425116,
	153984193,
	3675473203,
	3343476521,
	1064866854,
	3680420864,
	1767892582,
	744758650,
	1519319503,
	2276611093,
	1426880966,
	2633130371,
	1446741360,
	2435054400,
	435429221,
	3669401835,
	933092024,
	4209271110,
	3290105390,
	1413662315,
	3513928062,
	1077785853,
	2021631368,
	1423699487,
	1068876755,
	2120901815,
	4188468543,
	131961260,
	2488675799,
	1641152947,
	115168927,
	330231874,
	2850754114,
	1809430156,
	1822107721,
	2064532783,
	3721046572,
	3512565361,
	803106487,
	3716251309,
	2992445106,
	1746653202,
	3972697109,
	2849617566,
	2534589327,
	1001210244,
	1328415626,
	1626646295,
	2995538501,
	2521108919,
	3654768780,
	32417469,
	193817059,
	1750583735,
	2674735073,
	2346291386,
	3271294718,
	3265820418,
	1416254276,
	3365863812,
	1404403376,
	516505552,
	3773208948,
	4144940484,
	1430544400,
	1268862154,
	2217202584,
	2908022696,
	355916122,
	539004493,
	718836251,
	1082572151,
	238213328,
	390939205,
	3043264555,
	2162532142,
	2114544056,
	3394697810,
	3523131524,
	600300561,
	3886638041,
	1982350912,
	1720428295,
	933205398,
	2597531625,
	3382649284,
	3014915558,
	2705543429,
	4257633223,
	4282288299,
	766375082,
	2756120947,
	377976310,
	2010389054,
	2860711835,
	3519864886,
	2775713665,
	2557996913,
	891398354,
	3609190705,
	3782053633,
	1358380044,
	2097407511,
	587703123,
	349505262,
	1312913862,
	706935758,
	767028979,
	2445950508,
	452351020,
	696250687,
	321657486,
	1768677545,
	810804565,
	1694362237,
	2007797722,
	1264920838,
	3374523516,
	2206530719,
	4116817094,
	623927022,
	2218630415,
	3613420592,
	3250873975,
	2952446692,
	3877027275,
	2896414922,
	3287349092,
	2318861297,
	3482496489,
	2563194959,
	2255803900,
	605602864,
	919005580,
	3072929548,
	3938633710,
	3247667175,
	1264851357,
	1561705728,
	534725268,
	835315305,
	2869588309,
	1955694561,
	487781586,
	2275662466,
	597211963,
	3078551403,
	2306246977,
	117698822,
	2781317046,
	2884567044,
	2193587873,
	2363277399,
	71501447,
	327394568,
	2739391114,
	2831296918,
	3404326357,
	2595446627,
	2756669323,
	3045926185,
	466359675,
	2727244247,
	2058033618,
	3898166818,
	3969814300,
	1863555924,
	3812756443,
	3254803008,
	3166991819,
	1631478380,
	3235579087,
	4095687067,
	793443893,
	2323814650,
	4027271643,
	2141384740,
	3263172030,
	2240582840,
	569740212,
	1634506681,
	4132362192,
	776079908,
	2858686092,
	2346790124,
	2934601397,
	2168724337,
	1665391897,
	3727243251,
	2515474659,
	3881194279,
	650367097,
	2539657518,
	1767447799,
	2072274194,
	3027157846,
	2425194132,
	4024807398,
	1915268960,
	2362341647,
	3935738944,
	819699067,
	3253960934,
	3687553076,
	216536661,
	2240226444,
	3973074921,
	1870669624,
	788622594,
	1198698306,
	1012965715,
	2745392175,
	1191403201,
	1482427218,
	103106535,
	261428209,
	3272931111,
	1531218220,
	808778210,
	1145088004,
	60192701,
	3100414644,
	4036845097,
	4203395201,
	1167549130,
	1158606749,
	1162230285,
	949295643,
	3046438339,
	1918178165,
	1477887514,
	4222842058,
	1464721716,
	1129928304,
	161007533,
	1890499016,
	3077190415,
	1167167044,
	1270514905,
	2372398717,
	3284966005,
	3422397391,
	1334976110,
	1325314544,
	2023152276,
	3779566603,
	518814684,
	2566514544,
	2339419141,
	2905870170,
	1798879480,
	3464001928,
	3750433537,
	1299047806,
	512955554,
	1179785778,
	3230888450,
	4140949582,
	2766184958,
	2302502917,
	1123963760,
	2288257085,
	1397974313,
	1545995274,
	978452933,
	1776856003,
	2349847778,
	101298480,
	3529955798,
	3937184496,
	361513884,
	1309468115,
	4250220510,
	1520708641,
	4058522530,
	4255728232,
	3882958867,
	4128603535,
	2640813814,
	3118269184,
	2571603661,
	275618457,
	3603652786,
	2119136831,
	4038565857,
	4285659174,
	891945583,
	1466037421,
	1226102803,
	3310258058,
	1752208920,
	4096714883,
	588969535,
	599294057,
	3896218551,
	3681718840,
	2217749257,
	611648169,
	2414729609,
	2093736314,
	1330042375,
	1032073858,
	850468060,
	3185399110,
	653210662,
	832784782,
	2521633500,
	983335309,
	1329576454,
	2455730232,
	2733138262,
	1495768715,
	2422005962,
	663522487,
	846439045,
	62440720,
	1892098224,
	4246489531,
	228715206,
	994527967,
	193469166,
	2579169528,
	1074457665,
	1830688247,
	1206185632,
	2129936603,
	2802535058,
	2426248831,
	797459875,
	1809880969,
	1464257942,
	3181518428,
	3526461799,
	3183167778,
	1633872967,
	2230970679,
	1975732938,
	3774489940,
	1240128502,
	2867128955,
	678319271,
	1825562762,
	2634057640,
	3865252245,
	1182012905,
	365775923,
	2181772221,
	1952555184,
	2620240008,
	3666413874,
	3422293493,
	3499148112,
	988062523,
	2981205682,
	4274948997,
	1704428387,
	3457361118,
	225287241,
	2050158196,
	257763003,
	3986688045,
	1459905209,
	3189787803,
	2278195374,
	3776618420,
	2040438510,
	1530648845,
	1706635382,
	3756278757,
	1302784073,
	1401530684,
	666718676,
	4242313482,
	4248931856,
	411185872,
	2741999622,
	1005070462,
	3214308084,
	3408943538,
	2936266209,
	3990661997,
	946007720,
	503621995,
	3726105915,
	3170921201,
	3367442045,
	1906124788,
	4011150407,
	1625728984,
	768005095,
	1641334641,
	648372919,
	2577072326,
	3312325004,
	1681385341,
	666086773,
	3845001836,
	1165307954,
	3740245870,
	3870061732,
	3585757951,
	1024089777,
	4293277303,
	1283141381,
	2260598310,
	941695432,
	915948376,
	3885222120,
	226559113,
	3697041061,
	2089096292,
	567567415,
	2721800023,
	1728056212,
	3447159466,
	3402126148,
	3728026165,
	1461287021,
	1382414087,
	2459507570,
	188012277,
	1943971979,
	2627665880,
	3509125021,
	695248020,
	1822283721,
	1173958009,
	3237179831,
	1161072059,
	866411749,
	1558115333,
	1885233650,
	943915367,
	4007317449,
	416176080,
	3455013896,
	2602752943,
	2608926626,
	225514697,
	1057201338,
	2238511874,
	762327283,
	1090333183,
	3771447892,
	373000027,
	3767780806,
	2923947184,
	824925120,
	1567728751,
	2014052797,
	1250841910,
	368603149,
	1777626099,
	42647445,
	348382215,
	51789996,
	3579522037,
	587253782,
	2680682039,
	2874755766,
	1096929346,
	2842568196,
	1055701597,
	1544875514,
	1381498905,
	1846523796,
	2231547570,
	233415434,
	2512875213,
	1669696074,
	68070371,
	4033578141,
	2681481517,
	788443093,
	1650288984,
	436345731,
	349680864,
	3564307372,
	3988550982,
	653289389,
	2841034142,
	1240094341,
	411102470,
	1099825042,
	4049719826,
	691061163,
	2842417644,
	2659242702,
	3724572669,
	3684436375,
	1985653476,
	2124742566,
	4074414829,
	4028996995,
	3977045190,
	1684083350,
	3630066984,
	3887273010,
	3008586398,
	3881519900,
	4131252449,
	1650036788,
	1936142927,
	1456041926,
	1092080539,
	3613962792,
	451459928,
	2035992488,
	469792763,
	3465614249,
	1498487404,
	2680389410,
	3502104854,
	2912874939,
	1644266841,
	2651349821,
	1657546978,
	2988916046,
	3852538118,
	189425762,
	3019107892,
	2047212121,
	3640249671,
	261586155,
	71929310,
	3621428889,
	3321821918,
	1581098148,
	3835149295,
	2606068340,
	2255894993,
	579932932,
	1976765073,
	4119890438,
	1097048408,
	3065114024,
	4000686095,
	815693290,
	1939545845,
	1702441027,
	1490458366,
	1925237458,
	1021093698,
	1209091352,
	2872052743,
	1596003233,
	2981862233,
	4017173934,
	3227390873,
	2974087609,
	1846684678,
	2457805603,
	2374966032,
	3389018345,
	999748158,
	2907468364,
	1426951581,
	1142162924,
	3189832196,
	773063444,
	1095737979,
	2718472679,
	894928436,
	3306347811,
	4198014287,
	3064628686,
	2624589981,
	228356856,
	2526768638,
	4040474158,
	1573528872,
	602513566,
	3538133636,
	1535236204,
	4042020578,
	3272005365,
	1984382277,
	874722259,
	728636342,
	1169888870,
	3293887675,
	3459037009,
	2899099062,
	3872144604,
	479578891,
	2180468199,
	1888624839,
	3465937675,
	1624626906,
	2886641112,
	2423691919,
	1189322339,
	2585681490,
	1787764635,
	4037813798,
	3479321132,
	3658575486,
	1380197501,
	2340239206,
	610290475,
	755956971,
	2243544680,
	3333724719,
	3005388626,
	4030826507,
	880829941,
	2109968527,
	3367706194,
	1191548746,
	1346941736,
	921110016,
	3696858125,
	2073775040,
	2237544099,
	1011059922,
	1794381917,
	2442448387,
	2494442380,
	2890614022,
};

std::vector<std::string> skins= { 
	"a_f_m_bevhills_01", "a_f_m_bevhills_02", "a_f_m_bodybuild_01", "a_f_m_business_02", "a_f_m_downtown_01", "a_f_m_eastsa_01", "a_f_m_eastsa_02", "a_f_m_fatbla_01", "a_f_m_fatcult_01",
	"a_f_m_fatwhite_01", "a_f_m_ktown_01", "a_f_m_ktown_02", "a_f_m_prolhost_01", "a_f_m_salton_01", "a_f_m_skidrow_01", "a_f_m_soucentmc_01", "a_f_m_soucent_01", "a_f_m_soucent_02", "a_f_m_tourist_01",
	"a_f_m_trampbeac_01", "a_f_m_tramp_01", "a_f_o_genstreet_01", "a_f_o_indian_01", "a_f_o_ktown_01", "a_f_o_salton_01", "a_f_o_soucent_01", "a_f_o_soucent_02", "a_f_y_beach_01", "a_f_y_bevhills_01",
	"a_f_y_bevhills_02", "a_f_y_bevhills_03", "a_f_y_bevhills_04", "a_f_y_business_01", "a_f_y_business_02", "a_f_y_business_03", "a_f_y_business_04", "a_f_y_eastsa_01", "a_f_y_eastsa_02", "a_f_y_eastsa_03",
	"a_f_y_epsilon_01", "a_f_y_fitness_01", "a_f_y_fitness_02", "a_f_y_genhot_01", "a_f_y_golfer_01", "a_f_y_hiker_01", "a_f_y_hippie_01", "a_f_y_hipster_01", "a_f_y_hipster_02", "a_f_y_hipster_03",
	"a_f_y_hipster_04", "a_f_y_indian_01", "a_f_y_juggalo_01", "a_f_y_runner_01", "a_f_y_rurmeth_01", "a_f_y_scdressy_01", "a_f_y_skater_01", "a_f_y_soucent_01", "a_f_y_soucent_02", "a_f_y_soucent_03",
	"a_f_y_tennis_01", "a_f_y_topless_01", "a_f_y_tourist_01", "a_f_y_tourist_02", "a_f_y_vinewood_01", "a_f_y_vinewood_02", "a_f_y_vinewood_03", "a_f_y_vinewood_04", "a_f_y_yoga_01", "a_m_m_acult_01",
	"a_m_m_afriamer_01", "a_m_m_beach_01", "a_m_m_beach_02", "a_m_m_bevhills_01", "a_m_m_bevhills_02", "a_m_m_business_01", "a_m_m_eastsa_01", "a_m_m_eastsa_02", "a_m_m_farmer_01", "a_m_m_fatlatin_01",
	"a_m_m_genfat_01", "a_m_m_genfat_02", "a_m_m_golfer_01", "a_m_m_hasjew_01", "a_m_m_hillbilly_01", "a_m_m_hillbilly_02", "a_m_m_indian_01", "a_m_m_ktown_01", "a_m_m_malibu_01", "a_m_m_mexcntry_01",
	"a_m_m_mexlabor_01", "a_m_m_og_boss_01", "a_m_m_paparazzi_01", "a_m_m_polynesian_01", "a_m_m_prolhost_01", "a_m_m_rurmeth_01", "a_m_m_salton_01", "a_m_m_salton_02", "a_m_m_salton_03", "a_m_m_salton_04",
	"a_m_m_skater_01", "a_m_m_skidrow_01", "a_m_m_socenlat_01", "a_m_m_soucent_01", "a_m_m_soucent_02", "a_m_m_soucent_03", "a_m_m_soucent_04", "a_m_m_stlat_02", "a_m_m_tennis_01", "a_m_m_tourist_01",
	"a_m_m_trampbeac_01", "a_m_m_tramp_01", "a_m_m_tranvest_01", "a_m_m_tranvest_02", "a_m_o_acult_01", "a_m_o_acult_02", "a_m_o_beach_01", "a_m_o_genstreet_01", "a_m_o_ktown_01", "a_m_o_salton_01",
	"a_m_o_soucent_01", "a_m_o_soucent_02", "a_m_o_soucent_03", "a_m_o_tramp_01", "a_m_y_acult_01", "a_m_y_acult_02", "a_m_y_beachvesp_01", "a_m_y_beachvesp_02", "a_m_y_beach_01", "a_m_y_beach_02",
	"a_m_y_beach_03", "a_m_y_bevhills_01", "a_m_y_bevhills_02", "a_m_y_breakdance_01", "a_m_y_busicas_01", "a_m_y_business_01", "a_m_y_business_02", "a_m_y_business_03", "a_m_y_cyclist_01", "a_m_y_dhill_01",
	"a_m_y_downtown_01", "a_m_y_eastsa_01", "a_m_y_eastsa_02", "a_m_y_epsilon_01", "a_m_y_epsilon_02", "a_m_y_gay_01", "a_m_y_gay_02", "a_m_y_genstreet_01", "a_m_y_genstreet_02", "a_m_y_golfer_01",
	"a_m_y_hasjew_01", "a_m_y_hiker_01", "a_m_y_hippy_01", "a_m_y_hipster_01", "a_m_y_hipster_02", "a_m_y_hipster_03", "a_m_y_indian_01", "a_m_y_jetski_01", "a_m_y_juggalo_01", "a_m_y_ktown_01",
	"a_m_y_ktown_02", "a_m_y_latino_01", "a_m_y_methhead_01", "a_m_y_mexthug_01", "a_m_y_motox_01", "a_m_y_motox_02", "a_m_y_musclbeac_01", "a_m_y_musclbeac_02", "a_m_y_polynesian_01", "a_m_y_roadcyc_01",
	"a_m_y_runner_01", "a_m_y_runner_02", "a_m_y_salton_01", "a_m_y_skater_01", "a_m_y_skater_02", "a_m_y_soucent_01", "a_m_y_soucent_02", "a_m_y_soucent_03", "a_m_y_soucent_04", "a_m_y_stbla_01",
	"a_m_y_stbla_02", "a_m_y_stlat_01", "a_m_y_stwhi_01", "a_m_y_stwhi_02", "a_m_y_sunbathe_01", "a_m_y_surfer_01", "a_m_y_vindouche_01", "a_m_y_vinewood_01", "a_m_y_vinewood_02", "a_m_y_vinewood_03",
	"a_m_y_vinewood_04", "a_m_y_yoga_01", "u_m_y_proldriver_01", "u_m_y_rsranger_01", "u_m_y_sbike", "u_m_y_staggrm_01", "u_m_y_tattoo_01", "csb_abigail", "csb_anita", "csb_anton",
	"csb_ballasog", "csb_bride", "csb_burgerdrug", "csb_car3guy1", "csb_car3guy2", "csb_chef", "csb_chin_goon", "csb_cletus", "csb_cop", "csb_customer",
	"csb_denise_friend", "csb_fos_rep", "csb_g", "csb_groom", "csb_grove_str_dlr", "csb_hao", "csb_hugh", "csb_imran", "csb_janitor", "csb_maude",
	"csb_mweather", "csb_ortega", "csb_oscar", "csb_porndudes", "csb_porndudes_p", "csb_prologuedriver", "csb_prolsec", "csb_ramp_gang", "csb_ramp_hic", "csb_ramp_hipster",
	"csb_ramp_marine", "csb_ramp_mex", "csb_reporter", "csb_roccopelosi", "csb_screen_writer", "csb_stripper_01", "csb_stripper_02", "csb_tonya", "csb_trafficwarden", "cs_amandatownley",
	"cs_andreas", "cs_ashley", "cs_bankman", "cs_barry", "cs_barry_p", "cs_beverly", "cs_beverly_p", "cs_brad", "cs_bradcadaver", "cs_carbuyer",
	"cs_casey", "cs_chengsr", "cs_chrisformage", "cs_clay", "cs_dale", "cs_davenorton", "cs_debra", "cs_denise", "cs_devin", "cs_dom",
	"cs_dreyfuss", "cs_drfriedlander", "cs_fabien", "cs_fbisuit_01", "cs_floyd", "cs_guadalope", "cs_gurk", "cs_hunter", "cs_janet", "cs_jewelass",
	"cs_jimmyboston", "cs_jimmydisanto", "cs_joeminuteman", "cs_johnnyklebitz", "cs_josef", "cs_josh", "cs_lamardavis", "cs_lazlow", "cs_lestercrest", "cs_lifeinvad_01",
	"cs_magenta", "cs_manuel", "cs_marnie", "cs_martinmadrazo", "cs_maryann", "cs_michelle", "cs_milton", "cs_molly", "cs_movpremf_01", "cs_movpremmale",
	"cs_mrk", "cs_mrsphillips", "cs_mrs_thornhill", "cs_natalia", "cs_nervousron", "cs_nigel", "cs_old_man1a", "cs_old_man2", "cs_omega", "cs_orleans",
	"cs_paper", "cs_paper_p", "cs_patricia", "cs_priest", "cs_prolsec_02", "cs_russiandrunk", "cs_siemonyetarian", "cs_solomon", "cs_stevehains", "cs_stretch",
	"cs_tanisha", "cs_taocheng", "cs_taostranslator", "cs_tenniscoach", "cs_terry", "cs_tom", "cs_tomepsilon", "cs_tracydisanto", "cs_wade", "cs_zimbor",
	"g_f_y_ballas_01", "g_f_y_families_01", "g_f_y_lost_01", "g_f_y_vagos_01", "g_m_m_armboss_01", "g_m_m_armgoon_01", "g_m_m_armlieut_01", "g_m_m_chemwork_01", "g_m_m_chemwork_01_p", "g_m_m_chiboss_01",
	"g_m_m_chiboss_01_p", "g_m_m_chicold_01", "g_m_m_chicold_01_p", "g_m_m_chigoon_01", "g_m_m_chigoon_01_p", "g_m_m_chigoon_02", "g_m_m_korboss_01", "g_m_m_mexboss_01", "g_m_m_mexboss_02", "g_m_y_armgoon_02",
	"g_m_y_azteca_01", "g_m_y_ballaeast_01", "g_m_y_ballaorig_01", "g_m_y_ballasout_01", "g_m_y_famca_01", "g_m_y_famdnf_01", "g_m_y_famfor_01", "g_m_y_korean_01", "g_m_y_korean_02", "g_m_y_korlieut_01",
	"g_m_y_lost_01", "g_m_y_lost_02", "g_m_y_lost_03", "g_m_y_mexgang_01", "g_m_y_mexgoon_01", "g_m_y_mexgoon_02", "g_m_y_mexgoon_03", "g_m_y_mexgoon_03_p", "g_m_y_pologoon_01", "g_m_y_pologoon_01_p",
	"g_m_y_pologoon_02", "g_m_y_pologoon_02_p", "g_m_y_salvaboss_01", "g_m_y_salvagoon_01", "g_m_y_salvagoon_02", "g_m_y_salvagoon_03", "g_m_y_salvagoon_03_p", "g_m_y_strpunk_01", "g_m_y_strpunk_02", "hc_driver",
	"hc_gunman", "hc_hacker", "ig_abigail", "ig_amandatownley", "ig_andreas", "ig_ashley", "ig_ballasog", "ig_bankman", "ig_barry", "ig_barry_p",
	"ig_bestmen", "ig_beverly", "ig_beverly_p", "ig_brad", "ig_bride", "ig_car3guy1", "ig_car3guy2", "ig_casey", "ig_chef", "ig_chengsr",
	"ig_chrisformage", "ig_clay", "ig_claypain", "ig_cletus", "ig_dale", "ig_davenorton", "ig_denise", "ig_devin", "ig_dom", "ig_dreyfuss",
	"ig_drfriedlander", "ig_fabien", "ig_fbisuit_01", "ig_floyd", "ig_groom", "ig_hao", "ig_hunter", "ig_janet", "ig_jay_norris", "ig_jewelass",
	"ig_jimmyboston", "ig_jimmydisanto", "ig_joeminuteman", "ig_johnnyklebitz", "ig_josef", "ig_josh", "ig_kerrymcintosh", "ig_lamardavis", "ig_lazlow", "ig_lestercrest",
	"ig_lifeinvad_01", "ig_lifeinvad_02", "ig_magenta", "ig_manuel", "ig_marnie", "ig_maryann", "ig_maude", "ig_michelle", "ig_milton", "ig_molly",
	"ig_mrk", "ig_mrsphillips", "ig_mrs_thornhill", "ig_natalia", "ig_nervousron", "ig_nigel", "ig_old_man1a", "ig_old_man2", "ig_omega", "ig_oneil",
	"ig_orleans", "ig_ortega", "ig_paper", "ig_patricia", "ig_priest", "ig_prolsec_02", "ig_ramp_gang", "ig_ramp_hic", "ig_ramp_hipster", "ig_ramp_mex",
	"ig_roccopelosi", "ig_russiandrunk", "ig_screen_writer", "ig_siemonyetarian", "ig_solomon", "ig_stevehains", "ig_stretch", "ig_talina", "ig_tanisha", "ig_taocheng",
	"ig_taostranslator", "ig_taostranslator_p", "ig_tenniscoach", "ig_terry", "ig_tomepsilon", "ig_tonya", "ig_tracydisanto", "ig_trafficwarden", "ig_tylerdix", "ig_wade",
	"ig_zimbor", "mp_f_deadhooker", "mp_f_freemode_01", "mp_f_misty_01", "mp_f_stripperlite", "mp_g_m_pros_01", "mp_headtargets", "mp_m_claude_01", "mp_m_exarmy_01", "mp_m_famdd_01",
	"mp_m_fibsec_01", "mp_m_freemode_01", "mp_m_marston_01", "mp_m_niko_01", "mp_m_shopkeep_01", "mp_s_m_armoured_01", "", "", "", "",
	"", "s_f_m_fembarber", "s_f_m_maid_01", "s_f_m_shop_high", "s_f_m_sweatshop_01", "s_f_y_airhostess_01", "s_f_y_bartender_01", "s_f_y_baywatch_01", "s_f_y_cop_01", "s_f_y_factory_01",
	"s_f_y_hooker_01", "s_f_y_hooker_02", "s_f_y_hooker_03", "s_f_y_migrant_01", "s_f_y_movprem_01", "s_f_y_ranger_01", "s_f_y_scrubs_01", "s_f_y_sheriff_01", "s_f_y_shop_low", "s_f_y_shop_mid",
	"s_f_y_stripperlite", "s_f_y_stripper_01", "s_f_y_stripper_02", "s_f_y_sweatshop_01", "s_m_m_ammucountry", "s_m_m_armoured_01", "s_m_m_armoured_02", "s_m_m_autoshop_01", "s_m_m_autoshop_02", "s_m_m_bouncer_01",
	"s_m_m_chemsec_01", "s_m_m_ciasec_01", "s_m_m_cntrybar_01", "s_m_m_dockwork_01", "s_m_m_doctor_01", "s_m_m_fiboffice_01", "s_m_m_fiboffice_02", "s_m_m_gaffer_01", "s_m_m_gardener_01", "s_m_m_gentransport",
	"s_m_m_hairdress_01", "s_m_m_highsec_01", "s_m_m_highsec_02", "s_m_m_janitor", "s_m_m_lathandy_01", "s_m_m_lifeinvad_01", "s_m_m_linecook", "s_m_m_lsmetro_01", "s_m_m_mariachi_01", "s_m_m_marine_01",
	"s_m_m_marine_02", "s_m_m_migrant_01", "u_m_y_zombie_01", "s_m_m_movprem_01", "s_m_m_movspace_01", "s_m_m_paramedic_01", "s_m_m_pilot_01", "s_m_m_pilot_02", "s_m_m_postal_01", "s_m_m_postal_02",
	"s_m_m_prisguard_01", "s_m_m_scientist_01", "s_m_m_security_01", "s_m_m_snowcop_01", "s_m_m_strperf_01", "s_m_m_strpreach_01", "s_m_m_strvend_01", "s_m_m_trucker_01", "s_m_m_ups_01", "s_m_m_ups_02",
	"s_m_o_busker_01", "s_m_y_airworker", "s_m_y_ammucity_01", "s_m_y_armymech_01", "s_m_y_autopsy_01", "s_m_y_barman_01", "s_m_y_baywatch_01", "s_m_y_blackops_01", "s_m_y_blackops_02", "s_m_y_busboy_01",
	"s_m_y_chef_01", "s_m_y_clown_01", "s_m_y_construct_01", "s_m_y_construct_02", "s_m_y_cop_01", "s_m_y_dealer_01", "s_m_y_devinsec_01", "s_m_y_dockwork_01", "s_m_y_doorman_01", "s_m_y_dwservice_01",
	"s_m_y_dwservice_02", "s_m_y_factory_01", "s_m_y_fireman_01", "s_m_y_garbage", "s_m_y_grip_01", "s_m_y_hwaycop_01", "s_m_y_marine_01", "s_m_y_marine_02", "s_m_y_marine_03", "s_m_y_mime",
	"s_m_y_pestcont_01", "s_m_y_pilot_01", "s_m_y_prismuscl_01", "s_m_y_prisoner_01", "s_m_y_ranger_01", "s_m_y_robber_01", "s_m_y_sheriff_01", "s_m_y_shop_mask", "s_m_y_strvend_01", "s_m_y_swat_01",
	"s_m_y_uscg_01", "s_m_y_valet_01", "s_m_y_waiter_01", "s_m_y_winclean_01", "s_m_y_xmech_01", "s_m_y_xmech_02", "u_f_m_corpse_01", "u_f_m_miranda", "u_f_m_promourn_01", "u_f_o_moviestar",
	"u_f_o_prolhost_01", "u_f_y_bikerchic", "u_f_y_comjane", "u_f_y_corpse_01", "u_f_y_corpse_02", "u_f_y_hotposh_01", "u_f_y_jewelass_01", "u_f_y_mistress", "u_f_y_poppymich", "u_f_y_princess",
	"u_f_y_spyactress", "u_m_m_aldinapoli", "u_m_m_bankman", "u_m_m_bikehire_01", "u_m_m_fibarchitect", "u_m_m_filmdirector", "u_m_m_glenstank_01", "u_m_m_griff_01", "u_m_m_jesus_01", "u_m_m_jewelsec_01",
	"u_m_m_jewelthief", "u_m_m_markfost", "u_m_m_partytarget", "u_m_m_prolsec_01", "u_m_m_promourn_01", "u_m_m_rivalpap", "u_m_m_spyactor", "u_m_m_willyfist", "u_m_o_finguru_01", "u_m_o_taphillbilly",
	"u_m_o_tramp_01", "u_m_y_abner", "u_m_y_antonb", "u_m_y_babyd", "u_m_y_baygor", "u_m_y_burgerdrug_01", "u_m_y_chip", "u_m_y_cyclist_01", "u_m_y_fibmugger_01", "u_m_y_guido_01",
	"u_m_y_gunvend_01", "u_m_y_hippie_01", "u_m_y_imporage", "u_m_y_justin", "u_m_y_mani", "u_m_y_militarybum", "u_m_y_paparazzi", "u_m_y_party_01", "u_m_y_pogo_01", "u_m_y_prisoner_01"
};


void record(std::ofstream& strm) {
	char path[] = "JTA\\";
	char scenarios_path[] = "JTA-Scenarios\\";

	_mkdir(path);
	
	// redefined in the loop in order to change it based on the task
	//int max_samples = 30 * 60 * 1 + 1;
	// prova meno tempo
	//int max_samples = 60 * 10 * 1 + 1;
	int max_samples = 0;

	DatasetAnnotator* S;

	int seq_number = 0;

	// task initialization
	char task[15] = "reID";
	bool secondCam = FALSE;
	int FPS;

	std::ofstream ped_variations("ped_variations.txt");

	//// prova create ped
	////Ped tPed;
	//Ped tPed1, tPed2;
	//Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
	//tPed1 = PED::CREATE_PED(26, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//ped_variations << ENTITY::GET_ENTITY_MODEL(tPed1) << "\n";
	//for (int i = 0; i <= 11; i++) {
	//	ped_variations << "Component: " << i << ", draw_vars: " << PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(tPed1, i);
	//	ped_variations << ", varId: " << PED::GET_PED_DRAWABLE_VARIATION(tPed1, i);
	//	ped_variations << ", texture_vars: " << PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(tPed1, i, PED::GET_PED_DRAWABLE_VARIATION(tPed1, i));
	//	ped_variations << ", textureID: " << PED::GET_PED_TEXTURE_VARIATION(tPed1, i);
	//	ped_variations<< "\n";
	//
	//}
	//ped_variations << "\n";

	//tPed2 = PED::CREATE_PED(5, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//ped_variations << ENTITY::GET_ENTITY_MODEL(tPed2) << "\n";
	//for (int i = 0; i <= 11; i++) {
	//	ped_variations << "Component: " << i << ", draw_vars: " << PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(tPed2, i);
	//	ped_variations << ", varId: " << PED::GET_PED_DRAWABLE_VARIATION(tPed2, i);
	//	ped_variations << ", texture_vars: " << PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(tPed1, i, PED::GET_PED_DRAWABLE_VARIATION(tPed2, i));
	//	ped_variations << ", textureID: " << PED::GET_PED_TEXTURE_VARIATION(tPed2, i);
	//	ped_variations << "\n";
	//}
	//ped_variations << "\n";

	//tPed = PED::CREATE_PED(26, 3513928062, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//if (ENTITY::IS_ENTITY_VISIBLE(tPed)) {
	//	PED::CREATE_PED(26, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//}
	//else {
	//	PED::CREATE_PED(26, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//	PED::CREATE_PED(4, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//}
	//ENTITY::SET_ENTITY_VISIBLE(tPed, TRUE, true);

	//tPed = PED::CREATE_PED(4, 3513928062, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//if (ENTITY::IS_ENTITY_VISIBLE(tPed)) {
	//	PED::CREATE_PED(26, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//}
	//else {
	//	PED::CREATE_PED(26, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//	PED::CREATE_PED(4, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//}
	//ENTITY::SET_ENTITY_VISIBLE(tPed, TRUE, true);

	// prova create ped
	//Ped tPed;
	//Ped tPed1, tPed2;
	//Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);

	//tPed1 = PED::CREATE_PED(26, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//for (int i = 0; i <= 11; i++) {
	//	PED::SET_PED_COMPONENT_VARIATION(tPed1, i, 0, 0, 0);
	//}

	////strm << tPed1 << " " << ENTITY::IS_ENTITY_ON_SCREEN(tPed1) << "\n";
	////strm << tPed1 << " " << ENTITY::IS_ENTITY_VISIBLE(tPed1) << "\n";

	////tPed = PED::CREATE_PED(5, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//tPed2 = PED::CREATE_PED(26, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//for (int i = 0; i <= 11; i++) {
	//	PED::SET_PED_COMPONENT_VARIATION(tPed2, i, 0, 0, 0);
	//}
	//strm << tPed2 << " " << ENTITY::IS_ENTITY_VISIBLE(tPed2) << "\n";

	WAIT(1000);
	//if (ENTITY::GET_ENTITY_MODEL(tPed1) == ENTITY::GET_ENTITY_MODEL(tPed1)) {
	//	PED::DELETE_PED(&tPed2);
	//}

	//Ped tPed = PED::CREATE_PED(26, 301491555, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//strm << tPed << " " << ENTITY::IS_ENTITY_VISIBLE(tPed) << "\n";

	////if (ENTITY::IS_ENTITY_VISIBLE(tPed1) and ENTITY::IS_ENTITY_VISIBLE(tPed2)) {
	//Ped tPed;
	//for (int i = 0; i < hashes.size(); i++) {

	//	if (i==511 || i==512 || i==513) {
	//		strm << hashes[i] << " " << 0 << "\n";
	//		continue;
	//	}
	//	STREAMING::REQUEST_MODEL(hashes[i]);
	//	WAIT(300);
	//	tPed = PED::CREATE_PED(26, hashes[i], coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//	for (int i = 0; i <= 11; i++) {
	//		PED::SET_PED_COMPONENT_VARIATION(tPed, i, 0, 0, 0);
	//	}
	//	//if (PED::IS_PED_HUMAN(tPed)) {
	//	//	strm << hashes[i] << ",\n";
	//	//}
	//	strm << hashes[i] << " " << ENTITY::IS_ENTITY_VISIBLE(tPed) << "\n";
	//	WAIT(50);
	//	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hashes[i]);
	//	WAIT(300);
	//	PED::DELETE_PED(&tPed);
	//	WAIT(50);
	//}


	//tPed1 = PED::CREATE_PED(26, 3349113128, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	////}

	//char skin[] = "g_m_m_armgoon_01";
	//Hash skin_hash = 68070371;
	//strm << skin << " " << skin_hash << "\n";
	//// loading model in momory
	//STREAMING::REQUEST_MODEL(skin_hash);
	//WAIT(300);
	//Ped tPed = PED::CREATE_PED(26, skin_hash, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//strm << tPed << " " << ENTITY::GET_ENTITY_MODEL(tPed) << "\n";
	//tPed = PED::CREATE_PED(26, skin_hash, coords.x, coords.y, coords.z, 0.0, TRUE, TRUE);
	//strm << tPed << " " << ENTITY::GET_ENTITY_MODEL(tPed) << "\n";

	//skin_hash = 1822283721;
	//strm << skin << " " << skin_hash << "\n";
	//// loading model in momory
	//STREAMING::REQUEST_MODEL(skin_hash);
	//WAIT(300);
	//tPed = PED::CREATE_PED(26, skin_hash, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//strm << tPed << " " << ENTITY::GET_ENTITY_MODEL(tPed) << "\n";
	//tPed = PED::CREATE_PED(26, skin_hash, coords.x, coords.y, coords.z, 0.0, TRUE, TRUE);
	//strm << tPed << " " << ENTITY::GET_ENTITY_MODEL(tPed) << "\n";
	// provare a unloadare il modello dalla memoria con:
	//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(skin_hash);


	//PED::CREATE_PED(26, hashes[510], coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//PED::CREATE_PED(26, hashes[511], coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//PED::CREATE_PED(26, hashes[512], coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//PED::CREATE_PED(26, hashes[513], coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	//PED::CREATE_PED(26, hashes[514], coords.x, coords.y, coords.z, 0.0, FALSE, TRUE);
	

	// Day sequences
	for (auto &p : fs::recursive_directory_iterator(scenarios_path)) {
		if (fs::is_regular_file(p)) {
			int nsamples = 0;
			std::string output_path = std::string(path) + std::string("seq_") + std::to_string(seq_number);
			_mkdir(output_path.c_str());

			FILE *f = fopen(p.path().string().c_str(), "r");
			fscanf(f, "%s %*s\n", task);
			fscanf(f, "%d", &secondCam);

			if (secondCam)
				FPS = 60;
			else
				FPS = 30;

			// 10 second video for debugging, put to 60 for final version
			max_samples = FPS * 10 * 1 + 1;
			strm << FPS << task << max_samples << "\n";

			// resetting pointer of the file
			fseek(f, 0, SEEK_SET);

			//S = new DatasetAnnotator(output_path, p.path().string().c_str(), max_samples, 0, task);
			S = new DatasetAnnotator(output_path, f, max_samples, 0, task);

			Sleep(10);
			while (nsamples < max_samples) {
				nsamples = (*S).update();
				WAIT(0);
			}
			delete static_cast <DatasetAnnotator *>(S);
			seq_number++;

			// closing file ? lol, already closed in dataset annotator class (update)
			//fclose(f);
		}
	}

	//// Night sequences
	//for (auto &p : fs::recursive_directory_iterator(scenarios_path)) {
	//	if (fs::is_regular_file(p)) {
	//		int nsamples = 0;
	//		std::string output_path = std::string(path) + std::string("\\seq_") + std::to_string(seq_number);
	//		_mkdir(output_path.c_str());
	//		S = new DatasetAnnotator(output_path, p.path().string().c_str(), max_samples, 1);
	//		Sleep(10);
	//		while (nsamples < max_samples) {
	//			nsamples = (*S).update();
	//			WAIT(0);
	//		}
	//		delete static_cast <DatasetAnnotator *>(S);
	//		seq_number++;
	//	}
	//}

}


void main()
{	
	std::ofstream strm("logme.txt");
	while (true) {
		if (IsKeyJustUp(VK_F8)) {
			strm << "gg\n";
			record(strm);
		}
		WAIT(0);

	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
