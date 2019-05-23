/*
//	by: Amir Mohsen Ekhtiary	|	https://amirmohsen.atbox.io
//
//  Data Structure:
//
//		    	Data Types	     		|	Student 0	|	  Student 1		|	...
//____________________________________________________________________________________
//	vector<string> name					|   Ali Hasani	|  Leila Saeedpoor	|	...
//	vector<string> dept					|  MathScience	|	 MathScience	|	...
//	vector<float> avg					|	  18.75		|	    19.4		|	...
//	vector< vector<Lesson> > lessons	|	lessons[0]	|	 lessons[1]		|	...
//
//	Indexes start from 0 to fit vector iteration
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

template<typename T>
T to(const string& str){
	T val;
	stringstream stream(str);
    stream >> val;
    return val;
}

struct Lesson {
	string name;
	float score;
};

class App {
	
	private:
		vector<string> name;
		vector<string> dept;
		vector<float> average;
		vector< vector<Lesson> > lessons;
		
	public:
		
		void push(vector<string> *files, string toPush){
			files->push_back(toPush);
		}
		
		float avg(vector<float> scores, vector<float> zaribs){
			float sum = 0, zarib = 0;
			for(unsigned short int i = 0;i < scores.size();i++){
				zarib += zaribs[i];
				sum += scores[i] * zaribs[i];
			}
			
			return sum / zarib;
		}
		
		void readfile(string file){
			ifstream inf(file.c_str());

    		if(!inf){
    			cout << "ERROR: Can not read file! => " << file.c_str();
        		exit(1);
    		}
    		
    		vector<float> zarib, scores;
    		vector<Lesson> lessons;
    		int line = 1;

    		while(inf){
        		string strInput;
        		getline(inf, strInput);
        		
        		if(line == 1){
        			stringstream s(strInput);
        			string part, name = "";
        			
        			int counter = 0;
        			while(s >> part){
        				if(counter < 2) name += (counter > 0) ? ' ' + part : part;
        				if(counter == 2) dept.push_back( part );
        				counter++;
					}
					App::name.push_back(name);
				} 
        		if(line > 1){
        			stringstream s(strInput);
        			string part;
        			Lesson thisLesson;
        			
        			int counter = 0;
        			while(s >> part){
        				if(counter == 0) thisLesson.name = part;
        				if(counter == 1) zarib.push_back( to<float>(part) );
        				if(counter == 2){
        					thisLesson.score = to<float>(part);
        					scores.push_back( to<float>(part) );
						}
        				counter++;
					}
					lessons.push_back(thisLesson);
					if(inf.eof()) break;
				}
        		line++;
    		}
    		
    		float avg = App::avg(scores, zarib);
    		App::average.push_back( avg );
    		App::lessons.push_back( lessons );
		}
		
		int max(vector<float> where){
			float max = 0;
			int index = 0;
			
			for(int i = 0;i < where.size();i++){
				if(where[i] > max){
					max = where[i];
					index = i;
				}
			}
			return index;
		}
		
		int min(vector<float> where){
			float min = where[0];
			int index = 0;
			for(int i = 1;i < where.size();i++){
				if(where[i] < min){
					min = where[i];
					index = i;
				}
			}
			return index;
		}
		
		void printMax(){
			int i = max(App::average);
			cout << App::average[i] << " : " << App::name[i] << endl;
		}
		
		void printMin(){
			int i = min(App::average);
			cout << App::average[i] << " : " << App::name[i] << endl;
		}
		
		void getScoreByName(){
			float score = 0;
			string input = "";
			
			cout << "Enter name of the student: ";
			getline(cin, input);
			
			for(int i = 0;i < App::name.size();i++){
				if(name[i] == input){
					score = average[i];
					break;
				}
			}
			
			if(score == 0) cout << "\t - No Result Found!" << endl;
			else cout << "\t" << score << endl;
			
			cin.clear();
		}
		
		void printByDept(string mode){
			string depart = "";
			
			cout << "Enter name of the Department: ";
			getline(cin, depart);
			
			vector<float> spec_scores;
			vector<int> spec_indexes;
			for(int i = 0;i < App::dept.size();i++){
				if(dept[i] == depart){
					spec_indexes.push_back( i );
					spec_scores.push_back( App::average[i] );
				}
			}
			
			if(spec_indexes.size() == 0){
				cout << "\t - No Result Found!" << endl;
				cin.clear();
			} else {
				int index = mode == "max" ? max(spec_scores) : min(spec_scores); // index of max / min
				
				index = spec_indexes[index];
				
				cout << App::dept[index] << " => " << App::name[index] << " : " << App::average[index] << endl;
				cin.clear();
			}
		}
		
		void printTopInLesson(){
			string lesson = "";
			float maxInLesson = 0;
			int maxIndex = 0;
			
			cout << "Enter name of the Lesson: ";
			getline(cin, lesson);
			
			for(int i = 0;i < App::lessons.size();i++){
				for(int j = 0;j < App::lessons[i].size();j++){
					if(App::lessons[i][j].name == lesson){
						if(App::lessons[i][j].score > maxInLesson){
							maxInLesson = App::lessons[i][j].score;
							maxIndex = i;
						}
					}
				}
			}
			
			cout << App::name[maxIndex] << ": " << maxInLesson << endl;
		}
	
};

int main(){
	vector<string> files;
	App app;
	
	app.push(&files, "Student_Files/student1.txt");
	app.push(&files, "Student_Files/student2.txt");
	app.push(&files, "Student_Files/student3.txt");
	app.push(&files, "Student_Files/student4.txt");
	app.push(&files, "Student_Files/student5.txt");
	app.push(&files, "Student_Files/student6.txt");
	app.push(&files, "Student_Files/student7.txt");
	app.push(&files, "Student_Files/student8.txt");
	app.push(&files, "Student_Files/student9.txt");
	app.push(&files, "Student_Files/student10.txt");
	app.push(&files, "Student_Files/student11.txt");
	app.push(&files, "Student_Files/student12.txt");
	app.push(&files, "Student_Files/student13.txt");
	app.push(&files, "Student_Files/student14.txt");
	app.push(&files, "Student_Files/student15.txt");
	
	// Read & Store files data
	for(int i = 0;i < files.size();i++)
		app.readfile(files[i]);
	
	printf("1-   Max Avg\n2-   Max Avg (Specific Field)\n3-   Min Avg\n4-   Min Avg (Specific Field)\n5-   Top in lesson\n6-   Avg (Specific Student)\n7-   Exit (Trash Cleaning)\n");
	unsigned short int command;
	
	while(true){
		cin >> command;
		cin.clear();
		cin.get();
		
		switch(command){
			case 1: app.printMax();break;
			case 2: app.printByDept("max");break;
			case 3: app.printMin();break;
			case 4: app.printByDept("min");break;
			case 5: app.printTopInLesson();break;
			case 6: app.getScoreByName();break;
			case 7: return 0;break;
		}
		
	}
}
