#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // กรณีที่ไม่ได้ป้อนตัวเลขใดๆ ตามหลังชื่อโปรแกรม
    if (argc == 1) {
        std::cout << "Please input numbers to find average.\n";
        return 0;
    }

    int count = argc - 1; // จำนวนตัวเลขที่รับเข้ามา (หักลบชื่อโปรแกรมออก)
    double sum = 0.0;

    // วนลูปอ่านค่า Argument ตั้งแต่ตำแหน่งที่ 1 เป็นต้นไป
    for (int i = 1; i < argc; ++i) {
        try {
            // แปลงข้อความ (string) เป็นตัวเลขทศนิยม (double) และบวกสะสม
            sum += std::stod(argv[i]);
        } catch (...) {
            // ดักจับกรณีที่ผู้ใช้ป้อนข้อความที่ไม่ใช่ตัวเลข
            std::cout << "Error: Invalid number format (" << argv[i] << ")\n";
            return 1;
        }
    }

    // คำนวณหาค่าเฉลี่ย
    double average = sum / count;

    // แสดงผลลัพธ์ตามรูปแบบที่โจทย์กำหนด
    std::cout << "---------------------------------\n";
    std::cout << "Average of " << count << " numbers = " << average << "\n";
    std::cout << "---------------------------------\n";

    return 0;
}
