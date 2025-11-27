#include <stdio.h>
#include <string.h>

#define MAX 100

// Struct luu thong tin dia diem (Ben xe, dia chi)
struct Location {
    char name[50];      // Ten dia diem
    char address[100];  // Dia chi cu the
};

// Struct luu thong tin chuyen xe
struct Trip {
    char tripId[20];            // Ma chuyen xe (Unique)
    struct Location departure;  // Diem di (Struct long Struct)
    struct Location destination;// Diem den
    char date[20];              // Ngay khoi hanh
    int totalSeats;             // Tong so ghe
    int bookedSeats;            // So ghe da duoc dat
};

// Struct luu thong tin hanh khach
struct Passenger {
    char name[50];  // Ten khach
    char phone[15]; // So dien thoai
};

// Struct luu thong tin ve xe
struct Ticket {
    char ticketId[20];          // Ma ve
    char tripId[20];            // Ma chuyen xe (Khoa ngoai lien ket voi Trip)
    struct Passenger passenger; // Thong tin khach
    int seatNumber;             // So ghe dat
    double price;               // Gia ve
    int paymentStatus;          // 0: Chua thanh toan, 1: Da thanh toan
    char date[20];              // Ngay dat ve
    int status;                 // 0: Hop le, 1: Bi khoa, 2: Da huy
};

// --- BIEN TOAN CUC (DATABASE TREN RAM) ---

struct Trip trips[MAX]; // Mang luu danh sach chuyen xe
int tripCount = 0;      // Bien dem so luong chuyen xe hien co

struct Ticket tickets[1000]; // Mang luu danh sach ve (Max 1000 ve)
int ticketCount = 0;         // Bien dem so luong ve hien co

// --- HAM TIEN ICH (HELPER FUNCTIONS) ---

// Ham xoa bo nho dem ban phim
// Tac dung: Xoa dau Enter (\n) thua con sot lai sau lenh scanf de tranh loi troi lenh fgets
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Ham kiem tra du lieu dau vao
// Tra ve 0 neu chuoi rong hoac chi chua toan dau cach (Space)
// Tra ve 1 neu chuoi co du lieu hop le
int hasData(char *str) {
    if (strlen(str) == 0)
		return 0; // Chuoi rong
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != ' ') { // Tim thay it nhat 1 ky tu khong phai dau cach
            return 1;
        }
    }
    return 0; // Toan dau cach
}

// Tim vi tri (index) cua chuyen xe trong mang trips dua theo tripId
// Tra ve -1 neu khong tim thay
int findTripIndex(char *tripId) {
    for (int i = 0; i < tripCount; i++) {
        if (strcmp(trips[i].tripId, tripId) == 0) {
            return i;
        }
    }
    return -1;
}

// Tim vi tri (index) cua ve trong mang tickets dua theo ticketId
int findTicketIndex(char *ticketId) {
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].ticketId, ticketId) == 0) {
            return i;
        }
    }
    return -1;
}

// F01: Them chuyen xe moi
void f01_AddTrip() {
    // Kiem tra mang day chua
    if (tripCount >= MAX) {
        printf("Danh sach chuyen xe da day!\n");
        return;
    }

    struct Trip newTrip;
    printf("\n1. THEM CHUYEN XE MOI\n");
    
    // Vong lap while(1) de bat buoc nguoi dung nhap dung, neu sai: bat nhap lai
    while (1) {
        printf("Nhap ma chuyen xe: ");
        fgets(newTrip.tripId, 20, stdin); // Nhap chuoi an toan
        
        // Xu ly xoa dau xuong dong (\n) o cuoi chuoi do fgets tao ra
        if (strlen(newTrip.tripId) > 0 && newTrip.tripId[strlen(newTrip.tripId) - 1] == '\n') {
            newTrip.tripId[strlen(newTrip.tripId) - 1] = '\0';
        }

        // Validate: Khong duoc de trong hoac nhap toan dau cach
        if (hasData(newTrip.tripId) == 0) {
            printf("Ma chuyen xe khong duoc de trong.\n");
            continue; // Quay lai dau vong lap
        }
        // Validate: Kiem tra trung ma chuyen
        if (findTripIndex(newTrip.tripId) != -1) {
            printf("Ma chuyen xe da ton tai. Vui long nhap lai.\n");
        } else {
            break; // Hop le thi thoat vong lap
        }
    }

    // Nhap ten diem di
    while (1) {
        printf("Ten diem di: ");
        fgets(newTrip.departure.name, 50, stdin);
        if (strlen(newTrip.departure.name) > 0 && newTrip.departure.name[strlen(newTrip.departure.name) - 1] == '\n') {
            newTrip.departure.name[strlen(newTrip.departure.name) - 1] = '\0';
        }
        if (hasData(newTrip.departure.name))
			break;
        printf("Ten diem di khong hop le.\n");
    }

    while (1) {
        printf("Dia chi diem di: ");
        fgets(newTrip.departure.address, 100, stdin);
        if (strlen(newTrip.departure.address) > 0 && newTrip.departure.address[strlen(newTrip.departure.address) - 1] == '\n') {
            newTrip.departure.address[strlen(newTrip.departure.address) - 1] = '\0';
        }
        if (hasData(newTrip.departure.address))
			break;
        printf("Dia chi diem di khong hop le.\n");
    }

    while (1) {
        printf("Ten diem den: ");
        fgets(newTrip.destination.name, 50, stdin);
        if (strlen(newTrip.destination.name) > 0 && newTrip.destination.name[strlen(newTrip.destination.name) - 1] == '\n') {
            newTrip.destination.name[strlen(newTrip.destination.name) - 1] = '\0';
        }
        if (hasData(newTrip.destination.name))
			break;
        printf("Ten diem den khong hop le.\n");
    }

    while (1) {
        printf("Dia chi diem den: ");
        fgets(newTrip.destination.address, 100, stdin);
        if (strlen(newTrip.destination.address) > 0 && newTrip.destination.address[strlen(newTrip.destination.address) - 1] == '\n') {
            newTrip.destination.address[strlen(newTrip.destination.address) - 1] = '\0';
        }
        if (hasData(newTrip.destination.address))
			break;
        printf("Dia chi diem den khong hop le.\n");
    }

    while (1) {
        printf("Ngay khoi hanh (dd/mm/yyyy): ");
        fgets(newTrip.date, 20, stdin);
        if (strlen(newTrip.date) > 0 && newTrip.date[strlen(newTrip.date) - 1] == '\n') {
            newTrip.date[strlen(newTrip.date) - 1] = '\0';
        }
        if (hasData(newTrip.date))
			break;
        printf("Ngay khoi hanh khong hop le.\n");
    }

    // Nhap tong so ghe (phai la so duong)
    do {
        printf("Tong so ghe: ");
        scanf("%d", &newTrip.totalSeats);
        clearInputBuffer(); // Xoa dau Enter thua sau khi nhap so
        if (newTrip.totalSeats <= 0)
		printf("So ghe khong hop le. So ghe can phai la mot so lon hon 0.\n");
    } while (newTrip.totalSeats <= 0);

    newTrip.bookedSeats = 0; // Khoi tao so ghe da dat la 0
    trips[tripCount++] = newTrip; // Them vao mang va tang bien dem
    printf("Them chuyen xe thanh cong!\n");
}

// F02: Cap nhat thong tin chuyen xe
void f02_UpdateTrip() {
    char id[20];
    printf("\n2. CAP NHAT CHUYEN XE\n");
    printf("Nhap ma chuyen can sua: ");
    fgets(id, 20, stdin);
    if (strlen(id) > 0 && id[strlen(id) - 1] == '\n') {
        id[strlen(id) - 1] = '\0';
    }

    int idx = findTripIndex(id);
    if (idx == -1) {
        printf("Khong tim thay chuyen xe!\n");
        return;
    }

    // Dung con tro de sua truc tiep du lieu trong mang
    struct Trip *t = &trips[idx];
    printf("Dang cap nhat cho chuyen xe: %s\n", t->tripId);

    while (1) {
        printf("Diem di moi: ");
        fgets(t->departure.name, 50, stdin);
        if (strlen(t->departure.name) > 0 && t->departure.name[strlen(t->departure.name) - 1] == '\n') {
            t->departure.name[strlen(t->departure.name) - 1] = '\0';
        }
        if (hasData(t->departure.name))
            break;
        	printf("Diem di khong duoc de trong.\n");
    }

    while (1) {
        printf("Dia chi di moi: ");
        fgets(t->departure.address, 100, stdin);
        if (strlen(t->departure.address) > 0 && t->departure.address[strlen(t->departure.address) - 1] == '\n') {
            t->departure.address[strlen(t->departure.address) - 1] = '\0';
        }
        if (hasData(t->departure.address))
            break;
        printf("Dia chi di khong duoc de trong.\n");
    }

    while (1) {
        printf("Diem den moi: ");
        fgets(t->destination.name, 50, stdin);
        if (strlen(t->destination.name) > 0 && t->destination.name[strlen(t->destination.name) - 1] == '\n') {
            t->destination.name[strlen(t->destination.name) - 1] = '\0';
        }
        if (hasData(t->destination.name))
            break;
        printf("Diem den khong duoc de trong.\n");
    }

    while (1) {
        printf("Dia chi den moi: ");
        fgets(t->destination.address, 100, stdin);
        if (strlen(t->destination.address) > 0 && t->destination.address[strlen(t->destination.address) - 1] == '\n') {
            t->destination.address[strlen(t->destination.address) - 1] = '\0';
        }
        if (hasData(t->destination.address))
            break;
        printf("Dia chi den khong duoc de trong.\n");
    }

    while (1) {
        printf("Ngay gio moi: ");
        fgets(t->date, 20, stdin);
        if (strlen(t->date) > 0 && t->date[strlen(t->date) - 1] == '\n') {
            t->date[strlen(t->date) - 1] = '\0';
        }
        if (hasData(t->date))
            break;
        printf("Ngay gio khong duoc de trong.\n");
    }

    // Logic: Tong so ghe moi khong duoc nho hon so ghe da dat
    int newTotalSeats;
    do {
        printf("Tong so ghe moi (Hien tai da dat: %d): ", t->bookedSeats);
        scanf("%d", &newTotalSeats);
        clearInputBuffer();
        if (newTotalSeats < t->bookedSeats) {
            printf("Tong ghe moi khong duoc nho hon so ghe da dat.\n");
        }
    } while (newTotalSeats < t->bookedSeats);
    
    t->totalSeats = newTotalSeats;
    printf("Cap nhat chuyen xe thanh cong!\n");
}

// F03: Dat ve xe
void f03_BookTicket() {
    if (ticketCount >= 1000) {
        printf("He thong ve da day!\n");
        return;
    }

    struct Ticket newTicket;
    printf("\n3: DAT VE XE\n");

    // 1. Nhap va kiem tra chuyen xe
    char tId[20];
    printf("Nhap ma chuyen xe muon dat: ");
    fgets(tId, 20, stdin);
    if (strlen(tId) > 0 && tId[strlen(tId) - 1] == '\n') {
        tId[strlen(tId) - 1] = '\0';
    }

    int tripIdx = findTripIndex(tId);
    if (tripIdx == -1) {
        printf("Khong tim thay chuyen xe!\n");
        return;
    }
    
    struct Trip *trip = &trips[tripIdx]; // Lay con tro de thao tac de hon

    // Kiem tra chuyen xe con cho trong khong
    if (trip->bookedSeats >= trip->totalSeats) {
        printf("Chuyen xe da het ghe trong!\n");
        return;
    }

    strcpy(newTicket.tripId, tId);
    
    // 2. Tu dong sinh Ma ve
    // Logic: Chuyen so nguyen thanh ky tu ASCII (cong them '0')
    int num = ticketCount + 1;
    newTicket.ticketId[0] = 'T'; // Ky tu dau la T
    newTicket.ticketId[1] = (num / 100) + '0';       // Hang tram
    newTicket.ticketId[2] = ((num % 100) / 10) + '0';// Hang chuc
    newTicket.ticketId[3] = (num % 10) + '0';        // Hang don vi
    newTicket.ticketId[4] = '\0';                    // Ket thuc chuoi
    
    printf("Ma ve duoc tao tu dong: %s\n", newTicket.ticketId);

    // 3. Nhap thong tin khach hang
    while (1) {
        printf("Ten hanh khach: ");
        fgets(newTicket.passenger.name, 50, stdin);
        if (strlen(newTicket.passenger.name) > 0 && newTicket.passenger.name[strlen(newTicket.passenger.name) - 1] == '\n') {
            newTicket.passenger.name[strlen(newTicket.passenger.name) - 1] = '\0';
        }
        if (hasData(newTicket.passenger.name))
			break;
        printf("Ten hanh khach khong hop le.\n");
    }

    while (1) {
        printf("So dien thoai: ");
        fgets(newTicket.passenger.phone, 15, stdin);
        if (strlen(newTicket.passenger.phone) > 0 && newTicket.passenger.phone[strlen(newTicket.passenger.phone) - 1] == '\n') {
            newTicket.passenger.phone[strlen(newTicket.passenger.phone) - 1] = '\0';
        }
        if (hasData(newTicket.passenger.phone))
			break;
        printf("So dien thoai khong hop le.\n");
    }

    while (1) {
        printf("Ngay dat ve hom nay: ");
        fgets(newTicket.date, 20, stdin);
        if (strlen(newTicket.date) > 0 && newTicket.date[strlen(newTicket.date) - 1] == '\n') {
            newTicket.date[strlen(newTicket.date) - 1] = '\0';
        }
        if (hasData(newTicket.date))
			break;
        printf("Ngay dat ve khong hop le.\n");
    }

    // 4. Chon ghe va kiem tra trung ghe
    int seat;
    int isSeatTaken;
    do {
        isSeatTaken = 0; // Mac dinh la ghe chua co nguoi
        printf("Chon so ghe (1 - %d): ", trip->totalSeats);
        scanf("%d", &seat);
        clearInputBuffer();

        // Validate so ghe hop le
        if (seat < 1 || seat > trip->totalSeats) {
            printf("So ghe khong hop le.\n");
            isSeatTaken = 1; // Bat nhap lai
            continue;
        }

        // Quet toan bo mang ve de xem ghe nay cua chuyen nay da co ai dat chua
        for (int i = 0; i < ticketCount; i++) {
            if (strcmp(tickets[i].tripId, tId) == 0 && tickets[i].seatNumber == seat && tickets[i].status != 2) {   // Cung chuyen, cung so ghe, ve chua bi huy
                printf("Ghe so %d da co nguoi dat.\n", seat);
                isSeatTaken = 1; // Da co nguoi -> Bat nhap lai
                break;
            }
        }
    } while (isSeatTaken);

    newTicket.seatNumber = seat;
    printf("Nhap gia ve: ");
    scanf("%lf", &newTicket.price);
    clearInputBuffer();

    newTicket.paymentStatus = 0; // Mac dinh chua thanh toan
    newTicket.status = 0;        // Mac dinh hoat dong tot

    tickets[ticketCount++] = newTicket; // Luu ve vao mang
    trip->bookedSeats++; // Tang so ghe da dat cua chuyen xe len 1

    printf("Dat ve thanh cong!\n");
}

// F04: Kiem tra tinh trang ve
void f04_CheckTicketStatus() {
    char id[20];
    printf("\n4. KIEM TRA TINH TRANG VE\n");
    printf("Nhap ma ve (ticketId): ");
    fgets(id, 20, stdin);
    if (strlen(id) > 0 && id[strlen(id) - 1] == '\n') {
        id[strlen(id) - 1] = '\0';
    }

    int idx = findTicketIndex(id);
    if (idx == -1) {
        printf("Khong tim thay ve!\n");
        return;
    }

    struct Ticket t = tickets[idx]; // Lay ban sao ve de xem
    int tripIdx = findTripIndex(t.tripId);
    struct Trip trip = trips[tripIdx]; // Lay thong tin chuyen xe tuong ung

    printf("\nTHONG TIN CHI TIET VE:\n");
    printf("Ma ve: %s | Ma chuyen: %s\n", t.ticketId, t.tripId);
    printf("Hanh khach: %s | SDT: %s\n", t.passenger.name, t.passenger.phone);
    printf("Chuyen di tu: %s -> Den: %s\n", trip.departure.name, trip.destination.name);
    printf("Ngay khoi hanh: %s | Ngay dat: %s\n", trip.date, t.date);
    printf("So ghe: %d | Gia ve: %f VND\n", t.seatNumber, t.price);
    
    // Toan tu 3 ngoi de in trang thai thanh toan
    printf("Trang thai thanh toan: %s\n", (t.paymentStatus == 1 ? "DA THANH TOAN" : "CHUA THANH TOAN"));
    
    printf("Trang thai ve: ");
    if (t.status == 0) printf("HOP LE\n");
    else if (t.status == 1) printf("DA KHOA\n");
    else printf("DA HUY\n");
}

// F05: Liet ke chuyen xe (Phan trang)
void f05_ListTrips() {
    printf("\n5. DANH SACH CHUYEN XE\n");
    if (tripCount == 0) {
        printf("Khong co chuyen xe nao.\n");
        return;
    }

    int pageNumber = 1;
    int pageSize = 10; // So luong chuyen xe tren 1 trang
    
    printf("Nhap so trang: ");
    char buf[10];
    fgets(buf, 10, stdin);
    if (buf[0] != '\n') sscanf(buf, "%d", &pageNumber);
    if (pageNumber < 1) pageNumber = 1;

    // Tinh toan tong so trang
    int totalPages = (tripCount + pageSize - 1) / pageSize;
    if (pageNumber > totalPages) pageNumber = totalPages;

    // Tinh vi tri bat dau va ket thuc cua mang can in
    int startIndex = (pageNumber - 1) * pageSize;
    int endIndex = startIndex + pageSize;
    if (endIndex > tripCount) endIndex = tripCount;

    printf("\n%-10s | %-15s | %-15s | %-12s | %-8s\n", "ID", "Diem di", "Diem den", "Ngay", "Ghe");
    printf("----------------------------------------------------------------------\n");
    
    for (int i = startIndex; i < endIndex; i++) {
        struct Trip t = trips[i];
        printf("%-10s | %-15s | %-15s | %-12s | %d/%d\n", 
               t.tripId, t.departure.name, t.destination.name, t.date, t.bookedSeats, t.totalSeats);
    }
    printf("----------------------------------------------------------------------\n");
    printf("Trang %d / %d (Tong so chuyen: %d)\n", pageNumber, totalPages, tripCount);
}

// F06: Thanh toan ve
void f06_PayTicket() {
    char id[20];
    printf("\n6. THANH TOAN VE\n");
    printf("Nhap ma ve: ");
    fgets(id, 20, stdin);
    if (strlen(id) > 0 && id[strlen(id) - 1] == '\n') {
        id[strlen(id) - 1] = '\0';
    }

    int idx = findTicketIndex(id);
    if (idx == -1) {
        printf("Khong tim thay ve!\n");
        return;
    }

    struct Ticket *t = &tickets[idx]; // Dung con tro de sua du lieu

    // Validate: Ve bi khoa hoac huy thi khong duoc thanh toan
    if (t->status == 1 || t->status == 2) {
        printf("LOI: Ve da bi khoa hoac huy. Khong the thanh toan!\n");
        return;
    }

    if (t->paymentStatus == 1) {
        printf("LOI: Ve nay da duoc thanh toan truoc do.\n");
        return;
    }

    t->paymentStatus = 1; // Cap nhat trang thai thanh toan
    printf("Thanh toan thanh cong!\n");
}

// F07: Quan ly ve (Khoa / Huy)
void f07_ManageTicket() {
    char id[20];
    int action;
    printf("\n7. KHOA VE / HUY VE\n");
    printf("Nhap ma ve: ");
    fgets(id, 20, stdin);
    if (strlen(id) > 0 && id[strlen(id) - 1] == '\n') {
        id[strlen(id) - 1] = '\0';
    }

    int idx = findTicketIndex(id);
    if (idx == -1) {
        printf("Khong tim thay ve!\n");
        return;
    }

    struct Ticket *t = &tickets[idx];

    if (t->status == 1 || t->status == 2) {
        printf("Ve nay da bi khoa/huy truoc do.\n");
        return;
    }

    printf("Chon hanh dong (1: KHOA VE, 2: HUY VE): ");
    scanf("%d", &action);
    clearInputBuffer();

    if (action == 1) { 
        t->status = 1;
        printf("Da khoa ve xe thanh cong.\n");
    } 
    else if (action == 2) { 
        if (t->paymentStatus == 1) {
            printf("LOI: Khong the huy ve xe da thanh toan!\n");
        } else {
            t->status = 2; 
            int tripIdx = findTripIndex(t->tripId);
            if (tripIdx != -1) {
                trips[tripIdx].bookedSeats--;
            }
            printf("Huy ve xe thanh cong.\n");
        }
    } else {
        printf("Lua chon khong hop le. Vui long chon lai.\n");
    }
}

// Ham main
int main() {
    int choice;
    while (1) {
        // Menu lua chon
        printf("+-----QUAN LY VE XE KHACH-----+\n");
        printf("|1. Them chuyen xe            |\n");
        printf("|2. Cap nhat chuyen xe        |\n");
        printf("|3. Dat ve                    |\n");
        printf("|4. Tra cuu ve                |\n");
        printf("|5. Danh sach chuyen xe       |\n");
        printf("|6. Thanh toan                |\n");
        printf("|7. Huy ve                    |\n");
        printf("|8. Bao cao doanh thu         |\n");
        printf("|0. Thoat                     |\n");
        printf("+-----------------------------+\n");
        printf("Chon chuc nang: ");
        
        // Kiem tra nhap lieu (tranh nhap chu cai vao o so)
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            choice = -1;
        } else {
            clearInputBuffer();
        }

        switch (choice) {
            case 1: 
				f01_AddTrip();
				break;
            case 2:
				f02_UpdateTrip();
				break;
            case 3:
				f03_BookTicket();
				break;
            case 4:
				f04_CheckTicketStatus();
				break;
            case 5:
				f05_ListTrips();
				break;
            case 6:
				f06_PayTicket();
				break;
            case 7:
				f07_ManageTicket();
				break;
            case 8:
				break;
            case 0:
				printf("Thoat chuong trinh.");
				return 0;
            default:
				printf("Lua chon khong hop le. Vui long nhap lua chon hop le tu 0 den 8\n");
        }
    }
    return 0;
}
