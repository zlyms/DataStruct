#include<stdio.h>

#define INFINITY 10086
#define MAXSZIEVNUM 10

typedef char Vertextype; // ���嶥������
typedef int Edgetype;     // ���������

// �����ڽӾ���ṹ
typedef struct {
    Vertextype vex[MAXSZIEVNUM];  // ���㼯��
    Edgetype edge[MAXSZIEVNUM][MAXSZIEVNUM]; // �߼���
    char vextag[MAXSZIEVNUM];     // �����ǣ����ڱ�Ƕ����Ƿ����
    int vnum, arcnum;              // �������ͱ���
} Adjmat;

// ��ʼ���ڽӾ���
void IniAdjmat(Adjmat* adj) {
    if (adj == NULL) {
        return;
    }
    adj->vnum = 0;
    adj->arcnum = 0;
    for (int i = 0; i < MAXSZIEVNUM; i++) {
        adj->vextag[i] = '#'; // ��Ӧλ��Ϊ#��Ϊ�սڵ�
    }
}

// ��ȡ�����ڶ��㼯���е�����
int Getindex(Adjmat* adj, Vertextype x) {
    for (int i = 0; i < MAXSZIEVNUM; i++) {
        if (adj->vex[i] == x) {
            return i; // ���ض����ڶ��㼯���е�����
        }
    }
    printf("�����ڸö���\n");
    return -1; // ���㲻���ڣ�����-1
}

// �ж϶���x�Ͷ���y�Ƿ��ڽ�
int Adjacent(Adjmat* adj, Vertextype x, Vertextype y) {
    int t = Getindex(adj, x); // ��ȡ����x������
    int e = Getindex(adj, y); // ��ȡ����y������
    if (adj == NULL || t < 0 || e < 0) {
        return 0; // �ڽӾ���Ϊ�ջ򶥵㲻���ڣ�����0
    }
    if (adj->edge[t][e] != 0 && adj->edge[e][t] != 0 && adj->edge[t][e] != INFINITY && adj->edge[e][t] != INFINITY) {
        return 2; // ����x�Ͷ���y�໥�ڽӣ�����2
    }
    else if (adj->edge[t][e] != 0 && adj->edge[t][e] != INFINITY) {
        return 1; // ����x�ڽӶ���y������1
    }
    else {
        return 0; // ����x�Ͷ���y���ڽӣ�����0
    }
}

// ��ӡ����x�������ھӶ���
void Neighbors(Adjmat* adj, Vertextype x) {
    if (adj == NULL) {
        return; // �ڽӾ���Ϊ�գ�ֱ�ӷ���
    }
    int k = Getindex(adj, x); // ��ȡ����x������
    if (k == -1) {
        printf("�����ڸö���\n"); // ���㲻���ڣ���ӡ������Ϣ
        return;
    }
    for (int i = 0; i < MAXSZIEVNUM; i++) {
        // ��ӡ�����붥��x�ڽӵĶ���
        if ((adj->edge[k][i] != 0 && adj->edge[k][i] != INFINITY) || (adj->edge[i][k] != 0 && adj->edge[k][i] != INFINITY)) {
            printf("%c-%c ", adj->vex[k], adj->vex[i]); // ��ӡ����x���ڽӶ��������
        }
    }
}

// ���붥��x���ڽӾ�����
void InsertVertex(Adjmat* adj, Vertextype x) {
    if (adj->vnum >= MAXSZIEVNUM) {
        printf("���㼯����\n"); // ���㼯����������ӡ������Ϣ
        return;
    }
    int i;
    for (i = 0; i < MAXSZIEVNUM; i++) {
        if (adj->vextag[i] == '#') {
            adj->vex[i] = x; // ���붥��x�����㼯����
            adj->vnum++;     // ��������1
            adj->vextag[i] = '^'; // ���¶�����
            break;
        }
    }
    for (int j = 0; j < MAXSZIEVNUM; j++) {
        adj->edge[j][i] = INFINITY; // ��ʼ������x����������ı�Ϊ�����
        adj->edge[i][j] = INFINITY; // ��ʼ���������㵽����x�ı�Ϊ�����
    }
}

// ɾ������x������ر�
void Deletevertex(Adjmat* adj, Vertextype x) {
    int k = Getindex(adj, x); // ��ȡ����x������
    adj->vextag[k] = '#';     // ������x�ı����Ϊ#
    for (int j = 0; j < MAXSZIEVNUM; j++) {
        adj->edge[j][k] = INFINITY; // ɾ������x����������ı�
        adj->edge[k][j] = INFINITY; // ɾ���������㵽����x�ı�
    }
    adj->vnum--; // ��������1
}

// ��ӴӶ���x������y�ı�
void Addedge(Adjmat* adj, Vertextype x, Vertextype y, int b) {//b==1����ͼ��b==0����ͼ
    int t = Getindex(adj, x); // ��ȡ����x������
    int e = Getindex(adj, y); // ��ȡ����y������
    if (adj == NULL || t == -1 || e == -1) {
        return; // �ڽӾ���Ϊ�ջ򶥵㲻���ڣ�ֱ�ӷ���
    }
    if (b == 0) {
        adj->edge[t][e] = 1; // ��ӴӶ���x������y�ı�
    }
    if (b == 1) {
        adj->edge[t][e] = 1; // ��ӴӶ���x������y�ı�
        adj->edge[e][t] = 1; // ��ӴӶ���y������x�ı�
    }
    adj->arcnum++; // ������1
}

// ɾ���Ӷ���x������y�ı�
void RemoveEdge(Adjmat* adj, Vertextype x, Vertextype y, int b)//b==1����ͼ��b==0����ͼ
{
    int t = Getindex(adj, x); // ��ȡ����x������
    int e = Getindex(adj, y); // ��ȡ����y������
    if (adj == NULL || t == -1 || e == -1) {
        return; // �ڽӾ���Ϊ�ջ򶥵㲻���ڣ�ֱ�ӷ���
    }
    if (b == 0) {
        adj->edge[t][e] = INFINITY; // ɾ���Ӷ���x������y�ı�
    }
    if (b == 1) {
        adj->edge[t][e] = INFINITY; // ɾ���Ӷ���x������y�ı�
        adj->edge[e][t] = INFINITY; // ɾ���Ӷ���y������x�ı�
    }
    adj->arcnum--; // ������1
}

// ��ȡ����x�ĵ�һ���ھӶ���
int FirstNeighbor(Adjmat* adj, Vertextype x) {
    int t = Getindex(adj, x); // ��ȡ����x������
    if (adj == NULL || t == -1) {
        return; // �ڽӾ���Ϊ�ջ򶥵㲻���ڣ�ֱ�ӷ���
    }
    for (int i = 0; i < MAXSZIEVNUM; i++) {
        // ���Ҷ���x�ĵ�һ���ھӶ���
        if (adj->edge[t][i] != 0 && adj->edge[t][i] != INFINITY) {
            return i; // ���ض���x�ĵ�һ���ھӶ��������
        }
    }
    return -1; // δ�ҵ�������-1
}

// ��ȡ����x�ڶ���y֮�����һ���ھӶ���
int NextNeighbor(Adjmat* adj, Vertextype x, Vertextype y) {
    int t = Getindex(adj, x); // ��ȡ����x������
    int e = Getindex(adj, y); // ��ȡ����y������
    if (adj == NULL || t == -1 || e == -1) {
        return; // �ڽӾ���Ϊ�ջ򶥵㲻���ڣ�ֱ�ӷ���
    }
    for (int i = y + 1; i < MAXSZIEVNUM; i++) {
        // ���Ҷ���x�ڶ���y֮�����һ���ھӶ���
        if (adj->edge[t][i] != 0 && adj->edge[t][i] != INFINITY) {
            return i; // ���ض���x�ڶ���y֮�����һ���ھӶ��������
        }
    }
    return -1; // δ�ҵ�������-1
}

// ��ȡ����x������y�ıߵ�ֵ
int Get_edge_value(Adjmat* adj, Vertextype x, Vertextype y) {
    int t = Getindex(adj, x); // ��ȡ����x������
    int e = Getindex(adj, y); // ��ȡ����y������
    if (adj == NULL || t == -1 || e == -1) {
        return; // �ڽӾ���Ϊ�ջ򶥵㲻���ڣ�ֱ�ӷ���
    }
    if (adj->edge[t][e] != 0 && adj->edge[t][e] != INFINITY) {
        return adj->edge[t][e]; // ���ض���x������y�ıߵ�ֵ
    }
}

// ���ö���x������y�ıߵ�ֵ
void Set_edge_value(Adjmat* adj, Vertextype x, Vertextype y, Edgetype v) {
    int t = Getindex(adj, x); // ��ȡ����x������
    int e = Getindex(adj, y); // ��ȡ����y������
    if (adj == NULL || t == -1 || e == -1) {
        return; // �ڽӾ���Ϊ�ջ򶥵㲻���ڣ�ֱ�ӷ���
    }
    if (adj->edge[t][e] != 0 && adj->edge[t][e] != INFINITY) {
        adj->edge[t][e] = v; // ���ö���x������y�ıߵ�ֵ
    }
}

// ������
int main() {
    Adjmat adj; // ����һ���ڽӾ���ṹ����adj
    IniAdjmat(&adj); // ��ʼ���ڽӾ���

    // ���붥��'A'��'B'
    InsertVertex(&adj, 'A');
    InsertVertex(&adj, 'B');

    // ��ӴӶ���'A'������'B'�ı�
    Addedge(&adj, 'A', 'B', 1);

    // �ж϶���'A'�Ͷ���'B'�Ƿ��ڽ�
    Adjacent(&adj, 'A', 'B');

    // ��ӡ����'A'�������ھӶ���
    Neighbors(&adj, 'A');

    // ��ȡ����'A'�ĵ�һ���ھӶ���
    FirstNeighbor(&adj, 'A');

    // ��ȡ����'B'�ڶ���'A'֮�����һ���ھӶ���
    NextNeighbor(&adj, 'B', 'A');

    // ��ȡ����'B'������'A'�ıߵ�ֵ
    Get_edge_value(&adj, 'B', 'A');

    // ɾ���Ӷ���'A'������'B'�ı�
    RemoveEdge(&adj, 'A', 'B', 1);

    return 0; // ����0��ʾ������������
}
