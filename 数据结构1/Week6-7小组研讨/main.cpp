#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct SearchItem   // ��ʾĳ���ʵ�ǰ��������״̬
{
    string word;    // �������ĵ���
    int pt;         // ��ʾ��ǰ�Ѿ�ƥ�䵽��λ��
    int cnt;        // ��ʾ�Ѿ����ֹ����ٴθõ���
    bool valid;     // ��ʾ�õ������ı��е�ǰ�����Ƿ񻹿���ƥ��
};

int main()
{
    vector<string> lines;       //����һ���յ�vector
    vector<SearchItem> search;
    string filename;
    fstream fs;
    // ���ı��ļ�
    while (fs.is_open() == false)
    {
        cout << "�������ļ�����" << endl;
        cin >> filename;
        fs.open(filename, fstream::in);
        if (fs.is_open())
            break;
        cout << "�޷����ļ�" << endl;
    }
   
    // ��ȡ�ı�
    string line;
    while (getline(fs, line))  // ʹ��getline���õض�ȡһ��
    {
        lines.push_back(line);
    }
    fs.close();
    
    // ��ȡҪ���ҵĵ���
    rewind(stdin);
    cout << "������Ҫ���ҵĵ��ʣ�����#��ʾ����" << endl;
    while (true)
    {
        string buffer;
        char ch;
        while (true)
        {
            ch = getchar();
            if (ch == '#' || ch == ' ')
                break;
            buffer += ch;
        }
        search.push_back({ buffer, -1, 0, true });
        if (ch == '#')
            break;
    }

    // ���ҵ��ʣ�����ÿһ��
    for (int line = 0; line < lines.size(); line++)
    {
        // ��ǰ����ɨ�裬article_pt��ʾ��ǰ�ı���ɨ�赽��λ��
        for (int article_pt = 0; article_pt < lines[line].length(); article_pt++)
        {
            // �ı��е�ǰλ���ַ�
            char ch = lines[line][article_pt];
            // ����ڵ�����
            if (isalpha(ch) || ch == '\'')
            {
                // ��д��ĸӦ��ת��Сд
                if (isupper(ch))//���ch�Ǵ�д��ĸ���򷵻�true
                    ch = tolower(ch);//���ch�Ǵ�д��ĸ���򷵻���Сд��ĸ����ʽ������ֱ�ӷ���ch
                // ������ÿ����Ҫ��ƥ��ĵ���
                for (int i = 0; i < search.size(); i++)
                {
                    // ����õ����Ѿ�������ƥ��ɹ���֮ǰĳһλ��ĸ��ͬ����ֱ������
                    if (search[i].valid == false)
                        continue;
                    // ׼����Ҫ����������ʵ���һ���ַ�
                    int pt = search[i].pt + 1;
                    // ����ı��еĵ��ʱ�Ҫ���ĵ��ʳ����϶�����ƥ��
                    if (pt >= search[i].word.length())
                        search[i].valid = false;    // �����Ժ�Ҳ����ƥ��
                    // ������ߵĵ�ǰ�ַ��Ƿ����
                    else if (search[i].word[pt] == ch)
                        search[i].pt = pt;          // ƥ��ɹ���׼��ƥ����һλ
                    else
                        search[i].valid = false;    // ƥ��ʧ�ܣ��������ƥ��
                }
            }
            else    // ����Ƕ��ſո�ȷָ���
            {
                for (int i = 0; i < search.size(); i++)
                {
                    // ���ǰһ����ĸ�Ƿ�ƥ��ɹ�
                    if (search[i].valid == true && search[i].pt == search[i].word.length() - 1)
                    {
                        search[i].cnt++;
                        cout << "����" << search[i].word << "��" << search[i].cnt << "�γ����ڵ�" << line + 1 << "��" << endl;
                    }
                    // ���¼���ÿһ�������ĵ��ʣ���������ƥ���ı��е��µ���
                    search[i].pt = -1;
                    search[i].valid = true;
                }
            }
        }
    }
    for (int i = 0; i < search.size(); i++)
        cout << "����" << search[i].word << "������" << search[i].cnt << "��" << endl;
    return 0;
}