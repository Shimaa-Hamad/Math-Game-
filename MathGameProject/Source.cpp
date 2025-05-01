#include <iostream>

using namespace std; 

enum enOperationType {Add=1 , Sub=2 , Mult=3 , Div=4 , MixOp=5};
enum enQuestionLevel {Easy =1 , Med=2 , Hard=3 , Mix=4};

struct stQuestion 
{
	enOperationType OpType;
	enQuestionLevel QuestionLevel; 
	short Number1 = 0;
	short Number2 = 0;
	short CorrectAnswer = 0;
	short PlayerAnswer = 0;
	bool AnswerResult = false; 
};
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enOperationType OperationType;
	enQuestionLevel QuestionsLevel;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPass = false; 
};

string GetOperationSympol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

string GetQuestionLevelName(enQuestionLevel QuestionLevel)
{
	string ArrQuestionLevelName[4] = { "Easy" , "Med" , "Hard" , "Mix" };
	return ArrQuestionLevelName[QuestionLevel - 1];
}

int RandomNumber(int From, int To)
{
	int RandNum= rand()%(To-From+1)+From;
	return RandNum;
}

void SetScreenColor(bool Right)
{
	if (Right)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

enOperationType ReadOperationType()
{
	short Op; 
	do
	{
		cout << "Enter OperationType : [1]Add , [2]Sub , [3]Mult , [4]Div , [5]MixOperations : ";
		cin >> Op; 
	} while (Op < 1 || Op>5);
	return enOperationType(Op);
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel;
	do
	{
		cout << "Enter QuestionLevel : [1]Easy , [2]Med , [3]Hard , [4]Mix : ";
		cin >>QuestionLevel  ;
	} while (QuestionLevel < 1 || QuestionLevel>4);
	return enQuestionLevel(QuestionLevel);
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions ;
	do
	{
		cout << "How Many Questions Do You Want To Answer : ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions>10);
	return NumberOfQuestions;
}

short SimpleCalculator(short Number1, short Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2; 
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default :
		return Number1 + Number2; 
	}
}

enOperationType GetRandomOperationType()
{
	short Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionLevel QuestionsLevel, enOperationType OperationType)
{
	stQuestion Question;
	if (QuestionsLevel == enQuestionLevel::Mix)
	{
		QuestionsLevel = (enQuestionLevel)RandomNumber(1, 3);
	}
	if (OperationType == enOperationType::MixOp)
	{
		OperationType = GetRandomOperationType();
	}
	Question.OpType = OperationType; 
	switch (QuestionsLevel)
	{
	case enQuestionLevel::Easy :
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionsLevel;
		return Question; 
	case enQuestionLevel::Med:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(1, 50);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;
	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;
	}
	return Question; 
}

void GenerateQuizz(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OperationType);
	}
}

short ReadPlayerAnswer()
{
	short Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintQuestions(stQuizz& Quizz , short QuestionNumber)
{
	cout << "\nQuestion[" << QuestionNumber+1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl; 
	cout << Quizz.QuestionList[QuestionNumber].Number2 << "  " << GetOperationSympol(Quizz.QuestionList[QuestionNumber].OpType);
	cout << "\n--------\n";
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].CorrectAnswer != Quizz.QuestionList[QuestionNumber].PlayerAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << "\nWrong Answer:-( \n";
		cout << "The Right Answer is " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;
		cout << "\nRight Answer:-)\n";
	}
	cout << "\n";
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectTheQuestionList(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintQuestions(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
string GetFinalResultText(bool Pass)
{
	if (Pass)
		return "Pass :-) ";
	else
		return  "Fail :-(";
}

void PrintFinalResult(stQuizz Quizz)
{
	cout << "\n\n-------------------------------------------------------\n\n";
	cout << "   Final Results " << GetFinalResultText(Quizz.IsPass) << endl;
	cout << "\n\n-------------------------------------------------------\n\n";
	cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << "Number Of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "Number Of Right Answers : " << Quizz.NumberOfRightAnswers << endl; 
	cout << "Question Level : " << GetQuestionLevelName(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type : " << GetOperationSympol(Quizz.OperationType) << endl;
	cout << "\n\n-------------------------------------------------------\n\n";
}

void StartMathGame()
{
	stQuizz Quizz; 
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.OperationType = ReadOperationType();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	GenerateQuizz(Quizz);
	AskAndCorrectTheQuestionList(Quizz);
	PrintFinalResult(Quizz);
}

void ResetGame()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetGame();
		StartMathGame();
		cout << "Do You Want To Play Again : ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}