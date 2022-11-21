/*********** 用字符数组存储和处理字符串
    字符串常量(例:"PROGRAM")
    各字符连续、顺序存放,每个字符占一个字节,以'\0'结尾,相当于一个隐含创建的字符常量数组
    "program"出现在表达式中,表示这一char数组的首地址
    首地址可以赋给char常量指针:
    const char *STRINGl ="program";
    
用字符数组表示字符串的缺点：
    执行连接、拷贝、比较等操作,都需要显式调用库函数,很麻烦
    当字符串长度很不确定时,需要用new动态创建字符数组,最后要用delete释放,很繁琐
    字符串实际长度大于为它分配的空间时,会产生数组下标越界的错误
解决办法：
    使用字符串类string表示字符串
    string实际上是对字符数组操作的封装
以下三种都是等效的写法：
    char str[8] = ('p', 'r', 'o', 'g', 'r', 'a'.'m', '\0');
    char str[8] = "program";
    char str[] = "program";

常用的场景一：构造函数
    string (): //缺省构造函数,建立一个长度为0的串
    string (const char *s): //用指针s所指向的字符串常量初始化string类的对象
    string (const string & rhs);//拷贝构造函数

    例:
        -string sl; //建立一个空字符串
        -string s2 = "abc" : //用常量建立个初值为" abc"的字符串
        -string s3 = s2; //执行拷贝构造函数用s2的值作为s3的初值
常见的场景二： 操作符
s + t   将串s和t连接成一个新串用
s = t   用t更新s 
s == t  判断s与t是否相等
s != t  判断s与t是否不等
s < t   判断s是否小于t(按字典顺序比较)
s <= t  判断s是否小于或等于t (按字典顺序比较)
s > t   判断s是否大于t (按字典顺序比较)
s >= t  判断s是否大于或等于t(按字典顺序比较)
s[i]    访问串下标为i的字符
例:
    string sl = "abc", s2 = "def";
    string s3 = sl + s2;//结果是"abcdef"
    bool s4 = (sl < s2); //结果是true
    char s5 = s2[1]; //结果是 'e'
***********/
#pragma region  示例6-23string类应用举例
#include <string> 
#include <iostream>
using namespace std;
//根据value的值输出true或false, title为提示文字inline 
void test(const char *title, bool value) {
    cout << title <<" returns "<< (value ? "true": "false") << endl;
}
int main() {
    string s1= "DEF";
    cout << "s1 is "<<s1 << endl;
    string s2;
    cout << "Please enter s2: ";
    cin >> s2;
    cout << "length of s2: " << s2.length() << endl;
    //比较运算符的测试
    test("s1 <= \"ABC\"", s1 <= "ABC");
    test("\"DEFI\" <= s1", "DEF" <= s1);
    //连接运算符的测试
    s2 += s1;
    cout << "s2 = s2 + sl: "<< s2 << endl;
    cout << "length of s2: " << s2.length() << endl;
    return 0;
}
#pragma endregion

/*********** 用getline输入整行字符串
    1、用cin的>>操作符输入字符串,会以空格作为分隔符,空格后的内容会在下一回输入时被读取
    2、用string头文件中的getline可以输入整行字符串,
        例如:
            getline(cin, s2);
    以其它字符作为分隔符输入字符串
        1、输入字符串时,可以使用其它分隔符作为字符串结束的标志(例如逗号、分号)
        2、把分隔符作为getline的第3个参数即可。
        例如:
            getline(cin, s2, ',');
 
***********/
#pragma region  示例6-24用 getline输入字符串
#include <iostream> 
#include <string> 
using namespace std;
int main () {
    for (int i= 0; i< 2; i++){
        string city, state;
        getline(cin, city, '.');
        getline (cin, state);
        cout << "City:" << city <<" State:" << state << endl;
    }
    return 0;
}
/* 输出结果为
Beijing,China
City: Beijing   State: China
San Francisco,the United States
City: San Francisco     State: the United States
 */
#pragma endregion


#pragma region  示例删除字符串中的某个字符或几个相同的字符
void erase (char text [], char del)
{
    int len = strlen(text); //原字符长度
    int count = 0;
    char* copy = (char*) malloc(len + 1);
    for (int i=0; i<len; i++)
    {
        char ch = text [i];
        if(ch != del )
        {
            copy [count] = ch;
            count ++;
        }
    }
    copy [count] = 0; // 添加结束符
    strcpy(text, copy);//拷回原字符串
    free (copy); //释放内存
};
int main()
{
    char str[] = "China is a great country with a long histor ";
    erase (str, 'a');
    return 0;
}

#pragma endregion

#pragma region 在字符串中插入字符 (效率慢 应为要每个都移动一下)
 // 当 字符串数组 定义的长度未填满。 利名放着 \0
void insert (char text [], int index, char ins)
{
    int len = strlen(text);
    for (int i = len; i >index; i--)
    {
        text[i] = text[i-1]; //后面的字符前移
    }
        text [index] = ins;
}
#pragma endregion