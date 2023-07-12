#include <iostream>
#include <string>
#include <vector>
using namespace std;   

class Premises{
protected:
	struct Room{
		string Call;
		int Square;
	};
	vector<Room*> Rooms;
	int CountRooms;
	static double PriceM2;
public:
	Premises(){
		CountRooms=0;
	}
	virtual ~Premises(){
		for(int i=0; i<CountRooms; i++){
			delete Rooms[i];
		}
	}
	static void PriceOfM2(double Price){
		PriceM2=Price;
	}
	void AddRoom(string Call, int Square){
		Rooms.push_back(new Room);
		CountRooms++;
		Rooms[CountRooms-1]->Call=Call;
		Rooms[CountRooms-1]->Square=Square;
	}
	void DelRoom(string Call="Комната"){ //Удаляется последняя добавленная комната с таким названием
		for(int i=CountRooms-1; i>-1; i--)
			if (Rooms[i]->Call==Call){
				delete Rooms[i];
				Rooms.erase(Rooms.begin() + i);
				CountRooms--;
				return;
			}
		cout << "Нет такой комнаты" << endl;
	}
	virtual double PriceCalc() const = 0;
};

class Flat: public Premises{
	int Floor;
	bool Noise;
public:
	Flat(int floor, bool noise): Premises(), Floor(floor), Noise(noise) {}
	~Flat(){}
	Flat(const Flat& a){
		CountRooms = a.CountRooms;
		Floor = a.Floor;
		Noise  = a.Noise;
		for(int i=0; i<CountRooms; i++){
			Rooms.push_back(new Room);
			Rooms[i]->Call=a.Rooms[i]->Call;
			Rooms[i]->Square=a.Rooms[i]->Square;
		}
	}
	virtual double PriceCalc() const{
		double Worth=0;
		for(int i=0; i<CountRooms; i++)
			Worth += Rooms[i]->Square*PriceM2;
		if (((Floor>5)||(Floor<2))&&(CountRooms))
			Worth -= 3*PriceM2;
		if ((!Noise)&&(CountRooms))
			Worth -= 3*PriceM2;
		return Worth;
	}
	const Flat& operator=(const Flat& a){
		Floor = a.Floor;
		Noise  = a.Noise;
		for(int i=0; i<CountRooms; i++){
			delete Rooms[i];
		}
		CountRooms = a.CountRooms;
		for(int i=0; i<CountRooms; i++){
			Rooms.push_back(new Room);
			Rooms[i]->Call=a.Rooms[i]->Call;
			Rooms[i]->Square=a.Rooms[i]->Square;
		}
		return *this;
	}
	friend ostream& operator<<(ostream &out, const Flat& a);
};

ostream& operator<<(ostream &out, const Flat& a){
	out << "Квартира" << endl;
	out << "Этаж: " << a.Floor << endl;
	out << "Шум: ";
	if (a.Noise) out << "Есть" << endl;
	else out << "Нет" << endl;
	out << "Кол-во комнат: " << a.CountRooms << endl;
	out << "Комнаты:" << endl;
	for(int i=0; i<a.CountRooms; i++){
		out << a.Rooms[i]->Call << " Площадь: " << a.Rooms[i]->Square << endl;
	}
	return out;
}

class House: public Premises{
	int LandArea;
	int NumStoreys;
public:
	House(int landarea, int numstoreys): Premises(), LandArea(landarea), NumStoreys(numstoreys) {}
	~House(){}
	House(const House& a){
		CountRooms = a.CountRooms;
		LandArea = a.LandArea;
		NumStoreys  = a.NumStoreys;
		for(int i=0; i<CountRooms; i++){
			Rooms.push_back(new Room);
			Rooms[i]->Call=a.Rooms[i]->Call;
			Rooms[i]->Square=a.Rooms[i]->Square;
		}
	}
	virtual double PriceCalc() const{
		double Worth=0;
		for(int i=0; i<CountRooms; i++)
			Worth += Rooms[i]->Square*PriceM2;
		Worth += 3*PriceM2*NumStoreys*(CountRooms!=0);
		Worth += LandArea*PriceM2/10;
		return Worth;
	}
	const House& operator=(const House& a){
		LandArea = a.LandArea;
		NumStoreys = a.NumStoreys;
		for(int i=0; i<CountRooms; i++){
			delete Rooms[i];
		}
		CountRooms = a.CountRooms;
		for(int i=0; i<CountRooms; i++){
			Rooms.push_back(new Room);
			Rooms[i]->Call=a.Rooms[i]->Call;
			Rooms[i]->Square=a.Rooms[i]->Square;
		}
		return *this;
	}
	friend ostream& operator<<(ostream &out, const House& a);
};

ostream& operator<<(ostream &out, const House& a){
	out << "Частный Дом" << endl;
	out << "Этажность: " << a.NumStoreys << endl;
	out << "Площадь участка: " << a.LandArea << endl;
	out << "Кол-во комнат: " << a.CountRooms << endl;
	out << "Комнаты:" << endl;
	for(int i=0; i<a.CountRooms; i++){
		out << a.Rooms[i]->Call << " Площадь: " << a.Rooms[i]->Square << endl;
	}
	return out;
}

double Premises::PriceM2 = 0;

int main(){
	string str;
	int a, b, k;
	double d;
	int marker=1;
	cout << "Какая цена за метр квадратный?" << endl;
	cin >> d;
	Premises::PriceOfM2(d);
	cout << "Дом или квартира?" << endl;
	cin >> str;
	if ((str=="дом")||(str=="Дом")){
		cout<<"Введите площадь участка и этажность"<<endl;
		cin >> a >> b;
		House Apar(a, b);
		while(marker){
			cout<<"Введите соответсвующую цифру для вызова метода"<<endl;
			cout<<"1, добавить комнату"<<endl;
			cout<<"2, удалить комнату"<<endl;
			cout<<"3, произвести расчёт"<<endl;
			cout<<"другая цифра, завершение программы"<<endl;
			cin >> k;
			switch(k){
				case 1:
					cout<<"Введите название и площадь"<<endl;
					cin >> str >> a;
					Apar.AddRoom(str, a);
					break;
				case 2:
					cout<<"Введите название"<<endl;
					cin >> str;
					Apar.DelRoom(str);
					break;
				case 3:
					cout<<Apar.PriceCalc()<<"$"<<endl;
					break;
				default:
					marker=0;
					break;
			}
		}
	}else{
		cout<<"Этаж и шумоизоляцию"<<endl;
		cin >> a >> b;
		Flat Apar(a,b);
		while(marker){
			cout<<"Введите соответсвующую цифру для вызова метода"<<endl;
			cout<<"1, добавить комнату"<<endl;
			cout<<"2, удалить комнату"<<endl;
			cout<<"3, произвести расчёт"<<endl;
			cout<<"другая цифра, завершение программы"<<endl;
			cin >> k;
			switch(k){
				case 1:
					cout<<"Введите название и площадь"<<endl;
					cin >> str >> a;
					Apar.AddRoom(str, a);
					break;
				case 2:
					cout<<"Введите название"<<endl;
					cin >> str;
					Apar.DelRoom(str);
					break;
				case 3:
					cout<<Apar.PriceCalc()<<"$"<<endl;
					break;
				default:
					marker=0;
			}
		}
	}
	return 0;
}
