#include<stdio.h>

#define INFINITY 10086
#define MAXSZIEVNUM 10

typedef char Vertextype; // 定义顶点类型
typedef int Edgetype;     // 定义边类型

// 定义邻接矩阵结构
typedef struct {
    Vertextype vex[MAXSZIEVNUM];  // 顶点集合
    Edgetype edge[MAXSZIEVNUM][MAXSZIEVNUM]; // 边集合
    char vextag[MAXSZIEVNUM];     // 顶点标记，用于标记顶点是否存在
    int vnum, arcnum;              // 顶点数和边数
} Adjmat;

// 初始化邻接矩阵
void IniAdjmat(Adjmat* adj) {
    if (adj == NULL) {
        return;
    }
    adj->vnum = 0;
    adj->arcnum = 0;
    for (int i = 0; i < MAXSZIEVNUM; i++) {
        adj->vextag[i] = '#'; // 对应位置为#，为空节点
    }
}

// 获取顶点在顶点集合中的索引
int Getindex(Adjmat* adj, Vertextype x) {
    for (int i = 0; i < MAXSZIEVNUM; i++) {
        if (adj->vex[i] == x) {
            return i; // 返回顶点在顶点集合中的索引
        }
    }
    printf("不存在该顶点\n");
    return -1; // 顶点不存在，返回-1
}

// 判断顶点x和顶点y是否邻接
int Adjacent(Adjmat* adj, Vertextype x, Vertextype y) {
    int t = Getindex(adj, x); // 获取顶点x的索引
    int e = Getindex(adj, y); // 获取顶点y的索引
    if (adj == NULL || t < 0 || e < 0) {
        return 0; // 邻接矩阵为空或顶点不存在，返回0
    }
    if (adj->edge[t][e] != 0 && adj->edge[e][t] != 0 && adj->edge[t][e] != INFINITY && adj->edge[e][t] != INFINITY) {
        return 2; // 顶点x和顶点y相互邻接，返回2
    }
    else if (adj->edge[t][e] != 0 && adj->edge[t][e] != INFINITY) {
        return 1; // 顶点x邻接顶点y，返回1
    }
    else {
        return 0; // 顶点x和顶点y不邻接，返回0
    }
}

// 打印顶点x的所有邻居顶点
void Neighbors(Adjmat* adj, Vertextype x) {
    if (adj == NULL) {
        return; // 邻接矩阵为空，直接返回
    }
    int k = Getindex(adj, x); // 获取顶点x的索引
    if (k == -1) {
        printf("不存在该顶点\n"); // 顶点不存在，打印错误信息
        return;
    }
    for (int i = 0; i < MAXSZIEVNUM; i++) {
        // 打印所有与顶点x邻接的顶点
        if ((adj->edge[k][i] != 0 && adj->edge[k][i] != INFINITY) || (adj->edge[i][k] != 0 && adj->edge[k][i] != INFINITY)) {
            printf("%c-%c ", adj->vex[k], adj->vex[i]); // 打印顶点x与邻接顶点的连接
        }
    }
}

// 插入顶点x到邻接矩阵中
void InsertVertex(Adjmat* adj, Vertextype x) {
    if (adj->vnum >= MAXSZIEVNUM) {
        printf("顶点集已满\n"); // 顶点集合已满，打印错误信息
        return;
    }
    int i;
    for (i = 0; i < MAXSZIEVNUM; i++) {
        if (adj->vextag[i] == '#') {
            adj->vex[i] = x; // 插入顶点x到顶点集合中
            adj->vnum++;     // 顶点数加1
            adj->vextag[i] = '^'; // 更新顶点标记
            break;
        }
    }
    for (int j = 0; j < MAXSZIEVNUM; j++) {
        adj->edge[j][i] = INFINITY; // 初始化顶点x到其他顶点的边为无穷大
        adj->edge[i][j] = INFINITY; // 初始化其他顶点到顶点x的边为无穷大
    }
}

// 删除顶点x及其相关边
void Deletevertex(Adjmat* adj, Vertextype x) {
    int k = Getindex(adj, x); // 获取顶点x的索引
    adj->vextag[k] = '#';     // 将顶点x的标记置为#
    for (int j = 0; j < MAXSZIEVNUM; j++) {
        adj->edge[j][k] = INFINITY; // 删除顶点x到其他顶点的边
        adj->edge[k][j] = INFINITY; // 删除其他顶点到顶点x的边
    }
    adj->vnum--; // 顶点数减1
}

// 添加从顶点x到顶点y的边
void Addedge(Adjmat* adj, Vertextype x, Vertextype y, int b) {//b==1无向图，b==0有向图
    int t = Getindex(adj, x); // 获取顶点x的索引
    int e = Getindex(adj, y); // 获取顶点y的索引
    if (adj == NULL || t == -1 || e == -1) {
        return; // 邻接矩阵为空或顶点不存在，直接返回
    }
    if (b == 0) {
        adj->edge[t][e] = 1; // 添加从顶点x到顶点y的边
    }
    if (b == 1) {
        adj->edge[t][e] = 1; // 添加从顶点x到顶点y的边
        adj->edge[e][t] = 1; // 添加从顶点y到顶点x的边
    }
    adj->arcnum++; // 边数加1
}

// 删除从顶点x到顶点y的边
void RemoveEdge(Adjmat* adj, Vertextype x, Vertextype y, int b)//b==1无向图，b==0有向图
{
    int t = Getindex(adj, x); // 获取顶点x的索引
    int e = Getindex(adj, y); // 获取顶点y的索引
    if (adj == NULL || t == -1 || e == -1) {
        return; // 邻接矩阵为空或顶点不存在，直接返回
    }
    if (b == 0) {
        adj->edge[t][e] = INFINITY; // 删除从顶点x到顶点y的边
    }
    if (b == 1) {
        adj->edge[t][e] = INFINITY; // 删除从顶点x到顶点y的边
        adj->edge[e][t] = INFINITY; // 删除从顶点y到顶点x的边
    }
    adj->arcnum--; // 边数减1
}

// 获取顶点x的第一个邻居顶点
int FirstNeighbor(Adjmat* adj, Vertextype x) {
    int t = Getindex(adj, x); // 获取顶点x的索引
    if (adj == NULL || t == -1) {
        return; // 邻接矩阵为空或顶点不存在，直接返回
    }
    for (int i = 0; i < MAXSZIEVNUM; i++) {
        // 查找顶点x的第一个邻居顶点
        if (adj->edge[t][i] != 0 && adj->edge[t][i] != INFINITY) {
            return i; // 返回顶点x的第一个邻居顶点的索引
        }
    }
    return -1; // 未找到，返回-1
}

// 获取顶点x在顶点y之后的下一个邻居顶点
int NextNeighbor(Adjmat* adj, Vertextype x, Vertextype y) {
    int t = Getindex(adj, x); // 获取顶点x的索引
    int e = Getindex(adj, y); // 获取顶点y的索引
    if (adj == NULL || t == -1 || e == -1) {
        return; // 邻接矩阵为空或顶点不存在，直接返回
    }
    for (int i = y + 1; i < MAXSZIEVNUM; i++) {
        // 查找顶点x在顶点y之后的下一个邻居顶点
        if (adj->edge[t][i] != 0 && adj->edge[t][i] != INFINITY) {
            return i; // 返回顶点x在顶点y之后的下一个邻居顶点的索引
        }
    }
    return -1; // 未找到，返回-1
}

// 获取顶点x到顶点y的边的值
int Get_edge_value(Adjmat* adj, Vertextype x, Vertextype y) {
    int t = Getindex(adj, x); // 获取顶点x的索引
    int e = Getindex(adj, y); // 获取顶点y的索引
    if (adj == NULL || t == -1 || e == -1) {
        return; // 邻接矩阵为空或顶点不存在，直接返回
    }
    if (adj->edge[t][e] != 0 && adj->edge[t][e] != INFINITY) {
        return adj->edge[t][e]; // 返回顶点x到顶点y的边的值
    }
}

// 设置顶点x到顶点y的边的值
void Set_edge_value(Adjmat* adj, Vertextype x, Vertextype y, Edgetype v) {
    int t = Getindex(adj, x); // 获取顶点x的索引
    int e = Getindex(adj, y); // 获取顶点y的索引
    if (adj == NULL || t == -1 || e == -1) {
        return; // 邻接矩阵为空或顶点不存在，直接返回
    }
    if (adj->edge[t][e] != 0 && adj->edge[t][e] != INFINITY) {
        adj->edge[t][e] = v; // 设置顶点x到顶点y的边的值
    }
}

// 主函数
int main() {
    Adjmat adj; // 定义一个邻接矩阵结构变量adj
    IniAdjmat(&adj); // 初始化邻接矩阵

    // 插入顶点'A'和'B'
    InsertVertex(&adj, 'A');
    InsertVertex(&adj, 'B');

    // 添加从顶点'A'到顶点'B'的边
    Addedge(&adj, 'A', 'B', 1);

    // 判断顶点'A'和顶点'B'是否邻接
    Adjacent(&adj, 'A', 'B');

    // 打印顶点'A'的所有邻居顶点
    Neighbors(&adj, 'A');

    // 获取顶点'A'的第一个邻居顶点
    FirstNeighbor(&adj, 'A');

    // 获取顶点'B'在顶点'A'之后的下一个邻居顶点
    NextNeighbor(&adj, 'B', 'A');

    // 获取顶点'B'到顶点'A'的边的值
    Get_edge_value(&adj, 'B', 'A');

    // 删除从顶点'A'到顶点'B'的边
    RemoveEdge(&adj, 'A', 'B', 1);

    return 0; // 返回0表示程序正常结束
}
