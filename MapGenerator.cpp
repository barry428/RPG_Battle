#include "MapGenerator.h"

std::map<int, Region> MapGenerator::regions;  // 存储所有大区域，使用区域ID作为键

struct SubArea {
    std::string id;
    std::string name;
    std::string description;
};

struct Area {
    std::string id;
    std::string name;
    std::string description;
    std::vector<SubArea> subAreas;
};

std::map<std::string, Area> createMap() {
    std::map<std::string, Area> gameMap;

    // 中央城市区域
    gameMap["Central City Region"] = {
            "R1", "中央城市区域", "现代科技与日常生活的中心。", {
                    {"SA1", "商业区", "购物中心和市场，需要贸易通行证。"},
                    {"SA2", "居住区", "住宅和公寓，需要居住许可证。"},
                    {"SA3", "行政区", "政府大楼和设施，高安全区，需要特别通行证。"},
                    {"SA4", "教育区", "学校和研究中心。"},
                    {"SA5", "医疗区", "医院和诊所。"}
            }
    };

    // 边境高地
    gameMap["Highland Frontier"] = {
            "R2", "边境高地", "高海拔探险和神秘的区域。", {
                    {"SA6", "观测站", "星际观测和研究站，需要安全许可。"},
                    {"SA7", "高地营地", "登山者和探险家的基地。"},
                    {"SA8", "矿区", "资源丰富的矿场，需要矿工通行证。"},
                    {"SA9", "遗迹地", "古老的神秘遗迹。"}
            }
    };

    // 禁区荒漠
    gameMap["Forbidden Wastes"] = {
            "R3", "禁区荒漠", "荒废和法外之地充满危险。", {
                    {"SA10", "废土", "荒废的城市区域。"},
                    {"SA11", "流放之地", "罪犯和流放者的居住地，高危区域。"},
                    {"SA12", "秘密实验室", "隐藏的科学研究设施，需要最高级别的通行证。"},
                    {"SA13", "商队营地", "在荒漠中穿行的商队停留点。"}
            }
    };

    // 根据需要继续添加更多区域
    // 古林地带
    gameMap["Ancient Forest"] = {
            "R4", "古林地带", "古老的森林深处，藏匿着未知的力量和生物。", {
                    {"SA14", "古树之心", "古老森林的中心，有强大的魔法。"},
                    {"SA15", "猎人营地", "猎人和探险者的基地。"},
                    {"SA16", "隐居者之地", "隐士和智者居住的地方。"},
                    {"SA17", "药草园", "珍稀药材的种植园。"}
            }
    };

    // 神秘岛屿
    gameMap["Mystic Isles"] = {
            "R5", "神秘岛屿", "远离大陆的岛屿群，充满了神秘与传说。", {
                    {"SA18", "主岛", "岛屿群的中心岛屿，有复杂的洞穴系统。"},
                    {"SA19", "术士之岛", "神秘的魔法用户居住的岛屿。"},
                    {"SA20", "传说遗迹", "古老文明的遗迹所在地。"},
                    {"SA21", "隐藏港口", "海盗和走私者的秘密基地。"}
            }
    };

    // 冰封领域
    gameMap["Frozen Realm"] = {
            "R6", "冰封领域", "永久覆盖着冰雪的寒冷领域，只有最勇敢的探险家才敢涉足。", {
                    {"SA22", "冰川城堡", "一个被冰雪覆盖的古老城堡。"},
                    {"SA23", "雪人村落", "神秘的雪人居住的地区。"},
                    {"SA24", "冰原", "广阔的冰原，危险且寒冷。"},
                    {"SA25", "冰穴", "深入冰层下的洞穴系统。"}
            }
    };

    // 火山地带
    gameMap["Volcanic Lands"] = {
            "R7", "火山地带", "活跃的火山和炽热的地表定义了这片危险而壮观的区域。", {
                    {"SA26", "火山口", "活跃的火山区。"},
                    {"SA27", "熔岩湖", "危险的熔岩湖，需要特殊装备。"},
                    {"SA28", "灰烬平原", "火山爆发后的灰烬覆盖的平原。"},
                    {"SA29", "温泉区", "温泉和地热区域。"}
            }
    };

    // 水域世界
    gameMap["Aquatic World"] = {
            "R8", "水域世界", "由水面和水下组成的独特生态系统，生活着多样的水生生物。", {
                    {"SA30", "浮城", "建在水面上的城市。"},
                    {"SA31", "水下城市", "高科技水下居住区域。"},
                    {"SA32", "暗礁区", "危险的珊瑚礁区域。"},
                    {"SA33", "深海遗迹", "深海中的古老遗迹。"}
            }
    };

    // 幻影领域
    gameMap["Phantom Realm"] = {
            "R9", "幻影领域", "超自然现象和神秘事件频发的区域，充满未知和奇迹。", {
                    {"SA38", "梦境森林", "充满幻象的神秘森林。"},
                    {"SA39", "幽灵城", "据说是幽灵居住的城市。"},
                    {"SA40", "镜像湖", "湖水如镜，具有反射真实与幻象的能力。"},
                    {"SA41", "虚空门", "通往未知世界的门户。"}
            }
    };

    return gameMap;
}


std::vector<NPC> createNpc() {
    std::vector<NPC> npcs = {
            {1,  "老者",       "一位年迈的智者，擅长解读古老的秘籍和符文。"},
            {2,  "商人",       "一个四处旅行的商人，出售稀有物品和珍贵的资源。"},
            {3,  "治安官",     "负责维护地区秩序的官员，经常巡查街道确保安全。"},
            {4,  "神秘顾客",   "总是带着面纱，购买奇特物品的神秘人物。"},
            {5,  "草药师",     "熟知各种草药和植物的治疗属性，能够制作有效的药剂。"},
            {6,  "古董收藏家", "收藏古董和罕见艺术品的热情收藏家。"},
            {7,  "铁匠",       "锻造武器和防具的能手，他的技艺在当地享有盛誉。"},
            {8,  "猎人",       "擅长追踪和狩猎野生动物，常提供狩猎服务。"},
            {9,  "旅行者",     "一个热爱冒险的旅行者，经常分享他的冒险故事。"},
            {10, "守夜人",     "在夜晚守护村庄的守夜人，警惕任何可疑活动。"},
            {11, "隐士",       "在深山中独居的隐士，偶尔下山交换必需品。"},
            {12, "术士",       "使用禁忌魔法的术士，许多人对他保持距离。"},
            {13, "图书管理员", "管理图书馆的老图书管理员，对书籍了如指掌。"},
            {14, "炼金术士",   "制作各种奇特药水的炼金术士，他的技术是顶尖的。"},
            {15, "流浪艺人",   "到处旅行表演的艺人，擅长多种表演艺术。"},
            {16, "园丁",       "维护城市花园的园丁，对植物有深入的了解。"},
            {17, "学者",       "研究历史和文化的学者，常常埋头于厚重的书籍。"},
            {18, "巫师",       "擅长使用元素魔法的巫师，有些孤傲但能力出众。"},
            {19, "船长",       "经验丰富的船长，熟悉远洋航行和海上生存技巧。"},
            {20, "仙女",       "森林中的神秘仙女，有时会帮助迷路的旅行者。"},
            {21, "修道士",     "虔诚的修道士，常在寺庙中祈祷，为人们带来祝福。"},
            {22, "酒馆老板",   "热情的酒馆老板，提供美酒和食物，聆听来自各地的故事。"},
            {23, "魔法商人",   "出售稀奇古怪魔法物品的商人，货物来源总是令人好奇。"},
            {24, "旧货商",     "专门收购和出售二手货物的商人，善于寻找价值。"},
            {25, "地图制作者", "制作和销售详尽地图的专家，对地理了解深刻。"},
            {26, "冒险家",     "曾经周游世界的冒险家，退休后讲述他的冒险故事。"},
            {27, "药剂师",     "制造和销售各种药剂的专家，擅长治疗疾病和伤口。"},
            {28, "法律顾问",   "提供法律咨询的顾问，帮助人们解决法律纠纷。"},
            {29, "银行家",     "管理地方银行，提供贷款和储蓄服务的银行家。"},
            {30, "建筑师",     "设计和监督建筑工程的专家，创造美观且实用的建筑作品。"},
            {31, "历史学家",   "研究和记录历史的学者，努力揭开历史的神秘面纱。"},
            {32, "探险家",     "勇敢的探险家，总是第一个踏入未知领域的人。"},
            {33, "驯兽师",     "训练和售卖各种动物的专家，与动物有着特别的连接。"},
            {34, "赏金猎人",   "追踪和捕捉通缉犯的猎人，以此为生。"},
            {35, "巫女",       "与灵界沟通，使用神秘仪式帮助人解决问题的巫女。"},
            {36, "剑术大师",   "剑术非常高超的大师，提供剑术训练和表演。"},
            {37, "音乐家",     "才华横溢的音乐家，能演奏多种乐器，为人们带来美妙的音乐。"},
            {38, "占卜师",     "使用各种占卜工具预测未来，提供指导和建议的占卜师。"},
            {39, "邮差",       "负责邮件和包裹传递的邮差，确保信息的流通。"},
            {40, "舞者",       "表演各种舞蹈的艺术家，擅长用舞蹈表达情感和故事。"}
    };
    return npcs;
}

void MapGenerator::generateMapData() {
    int regionId = 1, locationId = 100, npcId = 1000;
    std::random_device rd;

    std::map<std::string, Area> initMap = createMap();
    std::vector<NPC> initNpc = createNpc();

    // 遍历 gameMap
    for (const auto &areaPair: initMap) {
        const auto &area = areaPair.second;
        Region region;
        region.id = regionId++;
        region.name = area.name;
        region.description = area.description;

        // 遍历子区域
        for (const auto &subArea: area.subAreas) {
            Location location;
            location.id = locationId++;
            location.name = subArea.name;
            location.description = subArea.description;

            for (int k = 0; k < 5; ++k) {
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1, 40);
                int numNPCs = dis(gen);

                NPC npc;
                npc.id = npcId++;
                npc.name = initNpc[numNPCs].name;
                npc.description = initNpc[numNPCs].description;
                location.npcs.push_back(npc);
            }
            region.locations.push_back(location);
        }
        regions[region.id] = region;
        std::cout << std::endl; // 添加空行以更好地分隔不同的区域
    }
}

std::map<int, Region> MapGenerator::getMapData() {
    return regions;
}

void MapGenerator::printMapData() {
    for (auto &[id, region]: regions) {
        std::cout << "Region ID: " << id << ", Name: " << region.name << "\n";
        for (auto &location: region.locations) {
            std::cout << "  Location ID: " << location.id << ", Name: " << location.name << "\n";
            for (auto &npc: location.npcs) {
                std::cout << "    NPC ID: " << npc.id << ", Name: " << npc.name << "\n";
            }
        }
    }
}
