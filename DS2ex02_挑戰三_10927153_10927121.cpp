/////////////10927121_張善泓_10927153_吳上玲
#include <iostream>           // cout, endl
#include <fstream>            // open, is_open, close, ignore
#include <string>             // string, find_last_of, substr
#include <vector>             // vector, push_back
#include <cstdlib>            // system, atoi
#include <iomanip>            // setw

using namespace std;
using std::string ;

struct DATA {
			int num = 0 ; // 唯一序號
			string school_id ; // 學校編碼
			string school_name ; // 學校名稱
			string department_id ; // 科系代碼
			string department_name ; // 科系名稱
			string daytime ; // 進修別
		 	string grade ; // 等級別
			int student = 0 ; // 學生數
			string others ;

};


vector <DATA> list ;
vector <int> tree1 ;
vector <int> tree2 ;
int note1 = 0 ;
int note2 = 0 ;
class tree_23{
	protected:

	struct Tree {     //只存序號和不同的學校名
			vector <int> num ;
			vector <string> school ;
			bool have_child = false ;
			Tree * left = NULL ;
			Tree * middle = NULL ;
			Tree * right = NULL ;
			Tree * more = NULL ;
			Tree * fa = NULL ;
	};

		vector <Tree> step ;
		Tree * head = NULL ;
		Tree * temp = NULL ;
		int tree_height = 0 ;
		DATA data ;
		Tree need ;
	public:

		bool Is_num ( int &num ) {                                             // command防呆 (排除數字以外的輸入)
   			string numstr ;
   			cin >> numstr ;
			if ( numstr == "0" ) {                                             // 輸入本身為0
				num = 0 ;
	 			return true ;
 			} // if

			num = atoi( numstr.c_str() ) ;
  			if ( num == 0 ) return false ;
  			else return true ;
		} // Is_num()

		bool dataget ( string &filename, int mission ) {

			string before ;
			string str1 ;
			fstream file ;
			bool success = false ;
			list.clear() ;
			step.clear() ;
			char str[500] ;


			while ( !success ) {

			if ( mission == 1 ) {
			   cout << endl << "Input a file number ([0] Quit):" ;
			   cin >> filename ;
			   if ( filename == "0" ) return false ;
			   filename = "input" + filename + ".txt" ;
			} // if

			file.open( filename.c_str(), ios::in ) ;
			if ( !file ) {
				cout << endl << "### " << filename << " does not exist! ###" << endl << endl ;
				success = false;
			} // if
			else success = true ;

			} // while

			file.getline( str, sizeof(str) ) ;
			file.getline( str, sizeof(str) ) ;
			file.getline( str, sizeof(str) ) ;

			while ( getline( file, data.school_id, '\t') ) {
				data.num = list.size() + 1 ;
				getline( file, data.school_name, '\t') ;
				getline( file, data.department_id, '\t') ;
				getline( file, data.department_name, '\t') ;
				getline( file, data.daytime, '\t') ;
				getline( file, data.grade, '\t') ;

				if ( file.peek() == '\"' ) {
					getline( file, str1, '\t') ;
					str1 = str1.erase( 0, 1 ) ;
					str1 = str1.erase( 1, 1 ) ;
					str1 = str1.erase( 4, 1 ) ;
					data.student = atoi(str1.c_str());
				} // if
				else file >> data.student ;
				getline(  file, data.others ) ;
				list.push_back( data ) ;

				if ( list.size() == 1 ||  before != data.school_name ) {
					need.num.clear() ;
					need.school.clear() ;
					need.num.push_back(data.num) ;
					need.school.push_back(data.school_name) ;
					step.push_back( need ) ;
					before = data.school_name ;

				} // if

			} // while

			file.close() ;
			return true ;
		} // dataget()

		void split() {                                          //遇到find_pos放入的資料筆數 == 3 時，要分離合併節點
			if ( temp -> fa == NULL ) {                         //temp到達樹根
				note1 = note1 + 2 ;
			    head = new Tree ;
			    tree_height++ ;
				head -> have_child = true ;
				head -> num.push_back(temp->num[1]) ;
				head -> school.push_back(temp->school[1]) ;
				head -> left = temp ;
				temp -> fa = head ;
				head -> right = new Tree ;
				head -> right -> fa = head ;                    //都有一個指標指向父節點
				head -> right -> num.push_back(temp->num[2]) ;
				head -> right -> school.push_back(temp->school[2]) ;
				temp->num.erase(temp->num.begin()+1, temp->num.end()) ;
				temp->school.erase(temp->school.begin()+1, temp->school.end()) ;
				if ( temp->have_child ) {
					temp->fa->right->have_child = true ;
					head->right->right = temp->more ;
					temp->more->fa = head->right ;
					temp->more = NULL ;
					head->right->left = temp->right ;
					temp->right->fa = head->right ;
					temp->right = temp->middle ;
					temp->middle = NULL ;
				} //if
			} // if

			else if ( temp->fa->num.size() == 1 && temp->school[1].compare(temp->fa->school[0]) > 0 ){//父節點只有一筆資料且temp指向的資料較大
				note1++ ;
  	 			temp->fa->num.push_back(temp->num[1]) ;
				temp->fa->school.push_back(temp->school[1]) ;
				temp->fa->middle = temp ;
				temp->fa->right = new Tree ;
				temp->fa->right->fa = temp->fa ;
				temp->fa->right->num.push_back(temp->num[2]) ;
				temp->fa->right->school.push_back(temp->school[2]) ;
				temp->num.erase(temp->num.begin()+1, temp->num.end()) ;
				temp->school.erase(temp->school.begin()+1, temp->school.end()) ;

				if ( temp->have_child ) {                                                             //分裂完後確認是否有要繼承的子節點
					temp->fa->right->have_child = true ;
					temp->fa->right->right = temp->more ;
					temp->more->fa = temp->fa->right ;
					temp->more = NULL ;
					temp->fa->right->left = temp->right ;
					temp->right->fa = temp->fa->right ;
					temp->right = temp->middle ;
					temp->middle = NULL ;
				} // if

			} // else if
			else if ( temp->fa->num.size() == 1 && temp->school[1].compare(temp->fa->school[0]) < 0 ){//父節點只有一筆資料且temp指向的資料較小
				note1++ ;
	            temp->fa->num.insert(temp->fa->num.begin(), temp->num[1]) ;
				temp->fa->school.insert(temp->fa->school.begin(), temp->school[1]) ;
				temp->fa->middle = new Tree ;
				temp->fa->middle->fa = temp->fa ;
				temp->fa->middle->num.push_back(temp->num[2]) ;
				temp->fa->middle->school.push_back(temp->school[2]) ;
				temp->num.erase(temp->num.begin()+1, temp->num.end()) ;
				temp->school.erase(temp->school.begin()+1, temp->school.end()) ;

				if ( temp->have_child ) {                                                       //分裂完後確認是否有要繼承的子節點
					temp->fa->middle->have_child = true ;
					temp->fa->middle->right = temp->more ;
					temp->more->fa = temp->fa->middle ;
					temp->more = NULL ;
					temp->fa->middle->left = temp->right ;
					temp->right->fa = temp->fa->middle ;
					temp->right = temp->middle ;
					temp->middle = NULL ;
				} // if

			} // else if
			else if ( temp->fa->num.size() == 2 ){                                              //父節點有兩筆資料且temp指向的資料最大
			note1++ ;
				if ( temp->school[1].compare(temp->fa->school[1]) > 0 ) {
					temp->fa->school.push_back(temp->school[1]) ;
					temp->fa->num.push_back(temp->num[1]) ;
					temp->fa->more = new Tree ;
					temp->fa->more->fa = temp->fa ;
					temp->fa->more->school.push_back(temp->school[2]) ;
					temp->fa->more->num.push_back(temp->num[2]) ;

					if ( temp->have_child ) {                                                   //確認子節點
					   temp->fa->more->have_child = true ;
					   temp->fa->more->right = temp->more ;
					   temp->more->fa = temp->fa->more ;
					   temp->more = NULL ;
					   temp->fa->more->left = temp->right ;
					   temp->right->fa = temp->fa->more ;
					   temp->right = temp->middle ;
					   temp->middle = NULL ;
					} // if
				} // if
				else if ( temp->school[1].compare(temp->fa->school[0]) < 0 ) {                  //父節點有兩筆資料且temp指向的資料最小
					temp->fa->school.insert(temp->fa->school.begin(), temp->school[1]) ;
					temp->fa->num.insert(temp->fa->num.begin(), temp->num[1]) ;
					temp->fa->more = temp->fa->right ;
					temp->fa->right = temp->fa->middle ;
					temp->fa->middle = new Tree ;
					temp->fa->middle->fa = temp->fa ;
					temp->fa->middle->num.push_back(temp->num[2]) ;
					temp->fa->middle->school.push_back(temp->school[2]) ;

					if ( temp->have_child ) {
					   temp->fa->middle->have_child = true ;
					   temp->fa->middle->right = temp->more ;
					   temp->more->fa = temp->fa->middle ;
					   temp->more = NULL ;
					   temp->fa->middle->left = temp->right ;
					   temp->right->fa = temp->fa->middle ;
					   temp->right = temp->middle ;
					   temp->middle = NULL ;
					} // if
				} // else if
				else {                                                                          //父節點有兩筆資料且temp指向的資料要插入中間
					temp->fa->school.insert(temp->fa->school.begin()+1, temp->school[1]) ;
					temp->fa->num.insert(temp->fa->num.begin()+1, temp->num[1]) ;
					temp->fa->more = temp->fa->right ;
					temp->fa->right = new Tree ;
					temp->fa->right->fa = temp->fa ;
					temp->fa->right->num.push_back(temp->num[2]) ;
					temp->fa->right->school.push_back(temp->school[2]) ;

					if ( temp->have_child ) {
					   temp->fa->right->have_child = true ;
					   temp->fa->right->right = temp->more ;
					   temp->more->fa = temp->fa->right ;
					   temp->more = NULL ;
					   temp->fa->right->left = temp->right ;
					   temp->right->fa = temp->fa->right ;
					   temp->right = temp->middle ;
					   temp->middle = NULL ;
					} // if
				} // else
				temp->num.erase(temp->num.begin()+1, temp->num.end()) ;
				temp->school.erase(temp->school.begin()+1, temp->school.end()) ;
				temp = temp->fa ;													//temp往上指一個節點
				split() ;                                                           //繼續判斷是否要分裂合併
			} // else if

			return ;
		} // split()

		void find_pos( Tree need ) {                                                //找到資料應該放置的位置
			if ( temp->have_child == false ) {                                         // 後面有沒有小孩
			   if ( need.school[0].compare( temp->school[0] ) < 0 ) {                  //比第一個數小
			   	temp->num.insert(temp->num.begin(), need.num[0]) ;
			   	temp->school.insert(temp->school.begin(), need.school[0]) ;
			   } // if
			   else if ( temp->school.size() == 1 && need.school[0].compare( temp->school[0] ) > 0 ) { // 比第一個數大
			   	temp->num.push_back(need.num[0]) ;
			   	temp->school.push_back(need.school[0]) ;
			   } // else if
			   else if ( temp->school.size() == 2 && need.school[0].compare( temp->school[1] ) < 0 ) { // 比第二個數小
			   	temp->num.insert(temp->num.begin()+1, need.num[0]) ;
			   	temp->school.insert(temp->school.begin()+1, need.school[0]) ;
			   } // else if
			   else if ( temp->school.size() == 2 && need.school[0].compare( temp->school[1] ) > 0 ) { // 比第二個數大
				temp->num.push_back(need.num[0]) ;
			   	temp->school.push_back(need.school[0]) ;
			   } // else if

               return ;
			} // if

			else if ( need.school[0].compare(temp->school[0]) < 0 ) temp = temp -> left ;
			else if ( temp->school.size() == 1 && need.school[0].compare(temp->school[0]) > 0 ) temp = temp -> right ;
			else if ( temp->school.size() == 2 && need.school[0].compare(temp->school[1]) < 0 ) temp = temp -> middle ;
			else if ( temp->school.size() == 2 && need.school[0].compare(temp->school[1]) > 0 ) temp = temp -> right ;
			find_pos(need) ;


		} // find_pos()

		void Insertion() {
			if ( step.empty() ) return ;


			need = step.front() ;

			if ( head == NULL ) {
				head = new Tree ;
				head->num.push_back(need.num[0]) ;
				head->school.push_back(need.school[0]) ;
				tree_height = 1 ;
				note1 = 1 ;
			} // if
			else {
				temp = head ;
				find_pos(need) ;
				if ( temp->num.size() > 2 ) split() ;
			} // else

			step.erase(step.begin()) ;
			Insertion() ;
		} // Insertion()

		bool search_tree(string sch) {
			if ( sch == "*" ) return true ;
			if ( temp == NULL ) return false ;
			
			if ( temp->school.size() == 1 ) {
				if ( temp->school[0].compare(sch) > 0 ) temp = temp->left ;
				else if ( temp->school[0].compare(sch) == 0 ) {
					 tree1.push_back(temp->num[0]) ;
					 return true ;
				}// else if
				else temp = temp->right ;
			} // if
			else {
				if ( temp->school[1].compare(sch) < 0 ) temp = temp->right ;
				else if ( temp->school[0].compare(sch) > 0 ) temp = temp->left ;
				else if ( temp->school[1].compare(sch) == 0 ) {
					 tree1.push_back(temp->num[1]) ;
					 return true ;
				}// eles if
				else if ( temp->school[0].compare(sch) == 0 ) {
					 tree1.push_back(temp->num[0]) ;
					 return true ;
				}// eles if
				else temp = temp->middle ;
			} // else
			
			
			search_tree(sch) ;
			
		} // search_tree()



		void Mission1 ( string &filename, int command, string sch ) {
			int number = 1 ;
			tree_height = 0 ;
			delete head ;
		 	delete temp ;
		 	head = NULL ;
			temp = head ;
			dataget( filename, command ) ;
			Insertion() ;
			if ( command==1 ) {
				
			cout << "note:" << note1 << endl ;
			cout << "Tree height =" << tree_height << endl ;
			if ( head != NULL ) {                                                        // 印出來，有時候要反印
			 	if ( head->num.size() == 1 || head->num[0] < head->num[1] ) {

			 	   for (int i = 0 ; i < head->num.size() ; i++ ) {
			 		    for ( int j = 0 ; j < list.size() ; j++ ) {
						    if ( head->school[i] == list[j].school_name ) {
							    cout << number << ": [" << list[j].num << "] " << list[j].school_name ;
								cout << ", " << list[j].department_name << ", " << list[j].daytime ;
								cout << ", " << list[j].grade << ", " << list[j].student << endl ;
								number++ ;
							} // if
						} // for
					} // for
				} // if
				else {
					for (int i = head->num.size()-1 ; i >= 0 ; i-- ) {                   // 若序號大的校名比較小，則反著印出來
			 		    for ( int j = 0 ; j < list.size() ; j++ ) {
						    if ( head->school[i] == list[j].school_name ) {
							    cout << number << ": [" << list[j].num << "] " << list[j].school_name ;
								cout << ", " << list[j].department_name << ", " << list[j].daytime ;
								cout << ", " << list[j].grade << ", " << list[j].student << endl ;
								number++ ;
							} // if
						} // for
					} // for
				} // else
			} // if

			 cout << endl << endl ;
			 
			} // if
			else if ( command == 3 ) {
			 	temp = head ;
			 	search_tree(sch) ;
			} // else if
			
		} // Mission1()

};

class tree_AVL : protected tree_23 {

public:

	struct TreeForAvl {
		int num ; // 唯一序號
		string school_id ; // 學校編碼
		string school_name ; // 學校名稱
		string department_id ; // 科系代碼
		string department_name ; // 科系名稱
		string daytime ; // 進修別
		string grade ; // 等級別
		int student  ; // 學生數
		vector <DATA> sameDepartment ; // 相同科系名稱
		TreeForAvl *left ;
		TreeForAvl *right ;

	}; // TreeForAvl

	TreeForAvl *temp = NULL ;

	int treeHigh( TreeForAvl *head ) {
		if ( head == NULL )
			return 0 ;
		else {
			int a = treeHigh( head -> left ) ;
			int b = treeHigh( head -> right ) ;
			if ( a > b )
				return a + 1 ;
			else
				return b + 1 ;

		} // else
	} // treeHigh


	TreeForAvl *rotateLL( TreeForAvl *x ) {
		TreeForAvl *y = x -> left ;
		x -> left = y -> right ;
		y -> right = x ;
		return y ;
	} // rotateLL()

	TreeForAvl *rotateRR( TreeForAvl *x ) {
		TreeForAvl *y = x -> right ;
		x -> right = y -> left ;
		y -> left = x ;
		return y ;
	} // rotateRR()

	TreeForAvl *rotateLR(TreeForAvl *x) {
		x->left = rotateRR( x->left ) ;
		return rotateLL(x) ;
	} // rotateLR()

	TreeForAvl *rotateRL(TreeForAvl *x) {
		x->right = rotateLL( x->right ) ;
		return rotateRR(x) ;
	} // rotateLR()

	void check( TreeForAvl *&head ) {
		int coefficient = treeHigh( head->left ) - treeHigh( head->right ) ;
	//	int bfl = treeHigh( head->left->left ) - treeHigh( head->left->right ) ;
	//	int bfr = treeHigh( head->right->left ) - treeHigh( head->right->right ) ;

		if ( coefficient < 2 && coefficient > -2 ) {
			return ;
		} // if
		else if ( coefficient >= 2 || coefficient <= -2 ) {

			if ( coefficient == 2 &&  ( treeHigh( head->left->left ) - treeHigh( head->left->right ) == 1 || treeHigh( head->left->left ) - treeHigh( head->left->right ) == 0 ) ) {
				head = rotateLL( head ) ;
			} // if
			else if ( coefficient == -2 && ( treeHigh( head->right->left ) - treeHigh( head->right->right ) == -1 || treeHigh( head->right->left ) - treeHigh( head->right->right ) == 0 ) ) {
				head = rotateRR( head ) ;
			} // if
			else if ( coefficient == 2 && treeHigh( head->left->left ) - treeHigh( head->left->right ) == -1  ) {
				head = rotateLR( head ) ;
			} // if
			else if ( coefficient == -2 && treeHigh( head->right->left ) - treeHigh( head->right->right ) == 1  ) {
				head = rotateRL( head ) ;
			} // if
		} // else if

	} // check()

	void whereShouldGo( TreeForAvl *&head, TreeForAvl *temp ) {
		DATA temp2 ;


		if ( head == NULL )
			head = temp ;
		else if ( temp -> department_name == head -> department_name ) {
			note2-- ;
			temp2.num = temp->num  ;
			temp2.school_id = temp->school_id ;
			temp2.school_name = temp->school_name ;
			temp2.department_id = temp->department_id;
			temp2.department_name = temp->department_name;
			temp2.daytime = temp->daytime;
			temp2.grade = temp->grade;
			temp2.student = temp->student;
			head -> sameDepartment.push_back( temp2 ) ;
			return ;
		} // else if
		else if ( temp -> department_name > head -> department_name ) {
			whereShouldGo( head -> right, temp ) ;
			check( head ) ;
		} // else if
		else if ( temp -> department_name < head -> department_name ) {
			whereShouldGo( head -> left, temp ) ;
			check( head ) ;
		} // else if

	} // whereShouldGo

	bool search_tree2(string sch) {
			if ( temp == NULL ) return false ;
			if ( sch == "*" ) return true ;
			if ( sch.compare( temp->department_name ) == 0) {
				tree2.push_back(temp->num) ;
				for (int i = 0 ; i < temp->sameDepartment.size() ; i++ ) tree2.push_back(temp->sameDepartment[i].num) ;
				return true ;
			} // if

			if ( temp->department_name.compare(sch) > 0 ) temp = temp->left ;
			else if ( temp->department_name.compare(sch) < 0 ) temp = temp->right ;
			
			search_tree2(sch) ;

	} // search_tree2()

	void Mission2( string filename, int command, string dep ) {
		TreeForAvl *head = NULL ;
		int x = 2 ;

		if ( dataget( filename, command ) ) {

			for( int i = 0 ; i < list.size() ; i++ ) {
				note2++ ;
				temp = new TreeForAvl ;
				temp->num = list[i].num ;
				temp->school_id = list[i].school_id;
				temp->school_name = list[i].school_name;
				temp->department_id = list[i].department_id;
				temp->department_name = list[i].department_name;
				temp->daytime = list[i].daytime;
				temp->grade = list[i].grade;
				temp->student = list[i].student;
				temp -> left = NULL ;
				temp -> right = NULL ;
				whereShouldGo( head, temp ) ;
				temp = NULL ;

			} // for
			if ( command==2 ) {
				cout << "note:" << note2 << endl ;
			cout << "Tree height  = " << treeHigh( head ) << endl ;
			cout << "1: [" << head->num << "}" << "	" << head->school_name << "	" << head->department_name << "	" << head->daytime << "	" << head->grade << "	" << head->student << endl ;

			for ( int j = 0 ;  j < head->sameDepartment.size() ; j++ ) {
				cout << x << ": [" << head->sameDepartment[j].num << "]" << " " << head->sameDepartment[j].school_name << "	" << head->sameDepartment[j].department_name ;
				cout << "	" << head->sameDepartment[j].daytime << "	" << head->sameDepartment[j].grade << "	" << head->sameDepartment[j].student << endl ;
				x++ ;
			} // for

		} // if
		
		else {
			temp = head ;
			search_tree2(dep) ;
		
		} // else
		} // if
		
			cout << endl ;
			
			
		
	} // Mission2()

};

void Mission3(string filename) {
	tree1.clear() ;
	tree2.clear() ;
	string sch ;
	string dep ;
	int j = 0 ;
	int i = 0 ;
	bool have = false ;
	cout << "Enter a college name to search [*]:" << endl ;
	cin >> sch ;
	cout << "Enter a department name to search [*]:" << endl ;
	cin >> dep ;
	
	tree_23 do1 ;
	tree_AVL do2 ;
	
	do1.Mission1(filename, 3, sch) ;
	do2.Mission2(filename, 3, dep) ;
	/*
	for ( int h = 0 ; h < tree1.size() ; h++ ) cout << list[tree1[h]-1].school_name << endl ;
	cout << endl ;
	for ( int h = 0 ; h < tree2.size() ; h++ ) cout << list[tree2[h]-1].department_name << endl ;
	*/
	
	if ( sch == "*" && dep == "*" ) {
		for (j = 0 ; j < list.size() ; j++ ) {
			cout << j+1 << ": [" << list[j].num << "] " << list[j].school_name ;
			cout << ", " << list[j].department_name << ", " << list[j].daytime ;
			cout << ", " << list[j].grade << ", " << list[j].student << endl ;
		} // for
	} // if
	else if ( sch == "*"  && tree2.size() > 0 ) {
		j = 0 ;
		i = 0 ;
		while ( i < tree2.size() ) {
			j = tree2[i] - 1 ;
			cout << i+1 << ": [" << list[j].num << "] " << list[j].school_name ;
			cout << ", " << list[j].department_name << ", " << list[j].daytime ;
			cout << ", " << list[j].grade << ", " << list[j].student << endl ;
			i++ ;
		} // while
	} // else if
	else if ( dep == "*" && tree1.size() > 0 ) {
		j = 0 ;
		i = 0 ;

		for ( j = tree1[0]-1 ; list[j].school_name.compare(sch) == 0 ; j++ ) {
			cout << i+1 << ": [" << list[j].num << "] " << list[j].school_name ;
			cout << ", " << list[j].department_name << ", " << list[j].daytime ;
		 	cout << ", " << list[j].grade << ", " << list[j].student << endl ;
		} // for
			
	} // else if
	else if ( tree1.size() > 0 && tree2.size() > 0 ){
		for ( j = 0 ; j < tree2.size() ; j++ ) {
			if ( list[tree2[j]-1].school_name.compare(sch) == 0 ) {
			   cout << 1 << ": [" << list[tree2[j]-1].num << "] " << list[tree2[j]-1].school_name ;
			   cout << ", " << list[tree2[j]-1].department_name << ", " << list[tree2[j]-1].daytime ;
			   cout << ", " << list[tree2[j]-1].grade << ", " << list[tree2[j]-1].student << endl ;
			} // if
		} // for
	}
	else cout << "nothing" << endl ;
	
	
	
	
} // Mission3()

int main() {
	bool one_first = false ;
	bool two_first = false ;
	string str ;
	bool temp = false ;
	tree_23 do1 ;
	tree_AVL do2 ;
	string filename ;
	while( true ) {
		cout << "*** Search Tree Utilities **" << endl ;
		cout << "* 0. QUIT                  *" << endl ;
		cout << "* 1. Build 2-3 tree        *" << endl ;
		cout << "* 2. Build AVL tree        *" << endl ;
		cout << "* 3. search                *" << endl ;
		cout << "*************************************" << endl ;
		cout << "Input a choice(0, 1, 2, 3):" ;
		int command ;
		note1 = 0 ;
		note2 = 0 ;
  	  	if ( !do1.Is_num( command ) ) cout << "Command does not exist!" << endl << endl ;
  	 	else if ( command > 3 || command < 0 ) cout << "Command does not exist!" << endl << endl ;
 		else if ( command == 0 ) break ;
  	  	else if ( command == 1 ) {
  	  		one_first = true ;
  	  		do1.Mission1( filename, command, str ) ;
  	  	} // else if
  	  	else if ( command == 2 && one_first ) {
  	  		do2.Mission2(filename, command, str ) ;
  	  		two_first = true ;
		} // else if
		else if ( command == 3 && one_first ) {
  	  		if ( two_first ) {
				Mission3(filename) ;
  	  		} // if
  	  		else cout << "### Choose 2 first. ###" << endl ;
		} // else if
		else cout << "### Choose 1 first. ###" << endl ;
	} // while
} // main()
