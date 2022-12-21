/***********浅拷贝 与 深拷贝
    浅拷贝
        实现对象间数据元素的一一对应复制。
    深拷贝
        当被复制的对象数据成员是指针类型时,不是复制该指针成员本身,而是将指针所指的对象进行复制。 
***********/
#pragma region 示例6-21 对象的浅拷贝  
#include <iostream>
#include <cassert>
using namespace std;
class Point {
   public:
        Point(): x(0), y(0) {
            cout<<"Default Constructor called."<<endl;
        }
        Point(int x, int y) : x(x), y(y){
            cout<< "Constructor called."<<endl;
        }
        ~Point(){
             cout<<"Destructor called."<<endl;
        }
        int getX() const { return x;}
        int getY() const { return y;}
        void move(int newX, int newY){
            x= newX;
            y= newY;
        }
    private:
        int x, y;
};
class ArrayOfPoints {//动态数组类
    public:
        ArrayOfPoints(int size): size(size) {
            points = new Point[size];
        }
        ~ArrayOfPoints() {
            cout << "Deleting..."<< endl;
            delete[] points;
        }
        Point &element(int index) {
            assert(index >= 0 && index < size);
            return points[index];
        }
    private:
        Point *points; //指向动态数组首地址
        int size;//数组大小

};
int main() {
    int count;
    cout <<"Please enter the count of points: ";
    cin >> count;
    ArrayOfPoints pointsArray1(count); //创建对象数组
    pointsArray1.element(0).move(5,10);
    pointsArray1.element(1).move(15,20);
    ArrayOfPoints pointsArray2 = pointsArray1; //创建副本
    cout << "Copy of pointsArray1:" << endl;
    cout << "Point_0 of array2: "<< pointsArray2.element(0).getX() 
        << pointsArray2.element(0).getY() << endl;
    cout << "Point_1 of array2: "<< pointsArray2.element(1).getX() 
        << pointsArray2.element(1).getY() << endl;

    pointsArray1.element(0).move(25, 30);
    pointsArray1.element(1).move(35, 40);
    cout << "After the moving of pointsArray1:" << endl;
    cout << "Point_0 of array2: "<< pointsArray2.element(0).getY() <<", "
        << pointsArray2.element(0).getY() << endl;
    cout << "Point_i of array2: "<< pointsArray2.element(1).getY() <<", "
        << pointsArray2.element(1).getY() << endl;
    return 0;
}

/* 运行结果如下
Please enter the number of 
points:2
Default Constructor called.
Default Constructor called.
Copy of pointsArrayl: 
Point_0 of array2: 5, 10 
Point_1 of array2: 15, 20 
After the moving of 
pointsArrayl:
Point_0 of array2: 25, 30
Point_1 of array2: 35, 40
Deleting...
Destructor called.
Destructor called.
Deleting...
接下来程序出现异常,也就是运行错误。
 */
#pragma endregion

#pragma region 解决问题使用深拷贝
#include <iostream>
#include <cassert>
#include <vector> 
using namespace std;
class Point{
    public:
        Point(): x(0), y(0) {
            cout<<"Default Constructor called."<<endl;
        }
        Point(int x, int y) : x(x), y(y){
            cout<< "Constructor called."<<endl;
        }
        ~Point(){
             cout<<"Destructor called."<<endl;
        }
        int getX() const { return x;}
        int getY() const { return y;}
        void move(int newX, int newY){
            x= newX;
            y= newY;
        }
    private:
        int x, y; 
};
class ArrayOfPoints {
    public:
        ArrayOfPoints(const ArrayOfPoints & pointsArray);
        ArrayOfPoints(int size): size(size) {
            points = new Point[size];
        }
        ~ArrayOfPoints() {
            cout << "Deleting..."<< endl;
            delete[] points;
        }
        Point &element(int index) {
            assert(index >= 0 && index < size);
            return points[index];
        }
    private:
        Point *points; //指向动态数组首地址
        int size;//数组大小
};
ArrayOfPoints::ArrayOfPoints(const ArrayOfPoints& v){
    size = v.size;
    points = new Point[size];
    for (int i = 0; i < size; i++)
        points[i] = v.points [i];
}
int main() {
    int count;
    cout <<"Please enter the count of points: ";
    cin >> count;
    ArrayOfPoints pointsArray1(count); //创建对象数组
    pointsArray1.element(0).move(5,10);
    pointsArray1.element(1).move(15,20);
    ArrayOfPoints pointsArray2 = pointsArray1; //创建副本
    cout << "Copy of pointsArray1:" << endl;
    cout << "Point_0 of array2: "<< pointsArray2.element(0).getX() 
        << pointsArray2.element(0).getY() << endl;
    cout << "Point_1 of array2: "<< pointsArray2.element(1).getX() 
        << pointsArray2.element(1).getY() << endl;

    pointsArray1.element(0).move(25, 30);
    pointsArray1.element(1).move(35, 40);
    cout << "After the moving of pointsArray1:" << endl;
    cout << "Point_0 of array2: "<< pointsArray2.element(0).getY() <<", "
        << pointsArray2.element(0).getY() << endl;
    cout << "Point_i of array2: "<< pointsArray2.element(1).getY() <<", "
        << pointsArray2.element(1).getY() << endl;
    return 0;
}

/*程序的运行结果如下:
Please enter the number of 
points:2
Default Constructor called.
Default Constructor called.
Default Constructor called.
Default Constructor called.
Copy of pointsArrayl: 
Point_0 of array2: 5, 10 
Point_1 of array2: 15, 20 
After the moving of 
pointsArrayl:
Point_0 of array2: 5, 10
Point_1 of array2: 15, 20
Deleting...
Destructor called.
Destructor called.
Deleting.
Destructor called.
 */
#pragma endregion


