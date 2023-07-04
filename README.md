# LexerParser

A simple lexical + syntax analyzer I made for a custom Tagalog programming language in fulfillment of the requirements of the subject Principles of Programming Languages.

A sample input:
```c++
-- Sample program
<-
this is a comment
->
ITAKDA _max 30

num UNA() {
	--Reserved Words
	num _numero, _num1 = 7, _num2 = 2, _num3, _num4, _num5, _num6, _num7, _num8, _num9, _num10, _num11 = 5;
	bil _ave;
	desi _kalahati;
	let _letra = 'a';
	kataga _tugon = "amen", _pangngalan[_max];
	_num1 += _num11;
	_num1 -= _num2;
	_kalahati = _num11 / _num1;
	_num4 = _num1 * _num2;
	_num5 = _num11 % _num1;
	_num5 = _num11 @ _num1;

	ILABAS.ANG("Ang halaga ay = %d", _num11);

	KUNG (_num1 == 7 AT _num2 == 2)
		KAYA GAWIN {_num3 = _num1 + _num2; }
	KUNGDI (_num1 > 7 O _num2 < 2 )
		_num4 = _num1 - _num2;
	KUNGDI (_num1 >= 5 O _num2 <= 3 )
		_num5 = _num1 * _num2;
	KUNGDI (_num1 /=/ 10)
		_num6 = _num1 / _num2;
	KUNGDI (HINDI(_num1 > 15))
		_num6 = _num1 + _num4 + _num5;
	IBA {
		_num6 += _num1 + 1;
		_num7 -= _num1 % _num2;
		_num8 *= _num1 @ _num2;
		_num9 /= _num1 ^ _num2;}
	
	PARA.SA (num _ikot = 0; _ikot < 3; _ikot += 1) { 
		ILABAS.ANG("Ikot " + _ikot);
		PARA.SA (num _bilang = 0; _bilang < 3; _bilang += 1) { 
			ILABAS.ANG("Pangngalan:");
			ILABAS.ANG(_tugon);
			ILABAS.ANG("Aksyon:" + _tugon);
			ILAGAY.SA(_pangngalan[_bilang]);
		}
		_ave = BLANKO;
		TIGIL;
	}
	
	IBALIK 0;
}
```
