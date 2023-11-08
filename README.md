# CPPModule09

<aside>
📌 STL

</aside>

- pdf

  https://cdn.intra.42.fr/pdf/pdf/101923/en.subject.pdf


## Module-specific rules

- 이 모듈의 각 연습을 수행하려면 반드시 표준 컨테이너를 사용해야 합니다.
- 컨테이너를 한 번 사용하면 나머지 모듈에서는 사용할 수 없습니다.

<aside>
ℹ️ exercises를 진행하기 전 subject 전체를 읽는 것이 좋습니다.

</aside>

<aside>
❗ 두 개의 컨테이너를 사용해야 하는 ex02를 제외하고, 각 연습문제 마다 적어도 하나의 컨테이너를 사용해야 합니다.

</aside>

## Exercise 00: Bitcoin Exchange

| Program name | btc |
| --- | --- |
| Turn-in directory | ex00/ |
| Files | Makefile, main.cpp, BitcoinExchange.{cpp, hpp} |
| Forbidden functions | None |
- 특정 날짜에 특정 금액의 비트코인 가치를 출력하는 프로그램을 만들어야 한다.
- 이 프로그램은 시간 경과에 따른 비트코인 가격을 나타내는 CVS형식의 데이터베이스를 사용해야 한다.
- 데이터베이스는 이 subject와 함께 제공된다.
- 프로그램은 두 번째 데이터베이스를 입력으로 받는다.
    - 평가 할 다양한 가격/날짜를 저장하는 데이터베이스
- 프로그램은 다음 규칙을 준수한다.
    - 프로그램 이름 :  btc
    - 프로그램은 반드시 파일을 인수로 받는다.
    - 이 파일의 각 줄은 다음 형식을 사용한다.
        - “date | value”
    - 유효한 날짜는 항상 다음 형식을 따른다.
        - Year-Month-Day
    - 유효한 값은 0에서 1000 사이의 float(부동 소수점) 또는 양의 정수여야 한다.

    <aside>
    ❗ 이 exercise의 유효성을 검사하려면 코드에서 컨테이너를 적어도 하나 이상 사용해야 한다. 발생 가능한 오류는 적절한 오류메세지로 처리해야 한다.

    </aside>

- 다음은 input.txt 파일의 예시이다.

```bash
$> head input.txt 
date | value
2011-01-03 | 3 
2011-01-03 | 2
2011-01-03 | 1 
2011-01-03 | 1.2
2011-01-09 | 1 
2012-01-11 | -1
2001-42-42 
2012-01-11 | 1
2012-01-11 | 2147483648 
$>
```

- 프로그램은 input file에 있는 값을 사용한다.
- 프로그램은 데이터베이스에 표시된 날짜에 따라 환율을 곱한 값의 결과를 표준 출력에 표시해야 한다.

<aside>
💡 입력에 사용된 날짜가 DB에 존재하지 않는 경우 DB에 포함된 가장 가까운 날짜를 사용해야 합니다. 
상위 날짜가 아닌 하위 날짜를 사용하도록 주의해라.

</aside>

- 다음은 프로그램 사용 예시입니다.

```bash
$> ./btc
Error: could not open file. 
$> ./btc input.txt
2011-01-03 => 3 = 0.9 
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3 
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42 
2012-01-11 => 1 = 7.1
Error: too large a number. 
$>
```

<aside>
❗ 경고 : 이 exercise의 유효성을 검사하는 데 사용한 컨테이너는 이 모듈의 나머지 부분에서는 더 이상 사용할 수 없다.

</aside>

-

## Exercise 01: Reverse Polish Notation

| Program name | RPN |
| --- | --- |
| Turn-in directory | ex01/ |
| Files | Makefile, main.cpp, 
RPN.{cpp, hpp} |
| Forbidden functions | None |
- 아래 제약 조건이 있는 프로그램을 만든다.
    - 프로그램 이름 : RPN
    - 프로그램은 Polish mathematical expression(역 폴란드 수학 식)을 argument로 사용해야 한다.
    - 이 연산에 사용되며 인수로 전달되는 숫자는 항상 10보다 작아야 한다.
        - 계산 자체 뿐만 아니라 결과는 이 규칙을 고려하지 않는다.
    - 프로그램은 이 표현 식을 처리하고 표준 출력에 올바른 결과를 출력해야 한다.
    - 프로그램 실행 중 오류가 발생하면 표준 출력에 오류 메세지가 표시되어야 한다.
    - 프로그램은 “+-/*” 이러한 토큰으로 연산을 처리할 수 있어야 한다.

    <aside>
    ❗ 이 문제의 유효성을 검사하려면 코드에서 컨테이너를 하나 이상 사용해야 한다.

    </aside>

    <aside>
    ℹ️ 괄호나 decimal numbers(소수)를 관리할 필요는 없다.

    </aside>

    - 다음은 표준 사용 예시:

    ```bash
    $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +" 
    42
    $> ./RPN "7 7 * 7 -" 
    42
    $> ./RPN "1 2 * 2 / 2 * 2 4 - +" 
    0
    $> ./RPN "(1 + 1)" 
    Error
    $>
    ```

    <aside>
    ❗ 경고 : 이전 문제에서 사용한 컨테이너는 여기서는 금지되어있다. 이 문제의 유효성을 검사하는 데 사용한 컨테이너는 이 모듈의 나머지 부분에서는 사용할 수 없다.

    </aside>


## Exercise 02: PmergeMe

| Program name | PmergeMe |
| --- | --- |
| Turn-in directory | ex02/ |
| Files | Makefile, main.cpp, 
PmergeMe.{cpp, hpp} |
| Forbidden functions | None |
- 이러한 제약 조건을 가진 프로그램을 만들어야 한다.
    - 프로그램 이름 : PmergeMe
    - 프로그램은 양의 정수 수열을 인수로 사용할 수 있어야 한다.
        - (positive integer sequence)
    - 프로그램은 merge-insert 정렬 알고리즘을 사용하여 양의 정수 시퀀스를 정렬해야 한다.

    <aside>
    ❗ 명확히 말하자면, Ford-Johnson algorithm을 사용해야 한다.

    </aside>

    - 프로그램이 실행되는 동안 에러가 발생하면, 에러 메세지를 표준 출력에 표시해야 한다.

    <aside>
    ❗ 이 문제에서 유효성을 검사하려면 코드에서 적어도 두 개의 서로 다른 컨테이너를 사용해야 한다. 프로그램은 적어도 3000개의 다른 정수를 처리할 수 있어야 한다.

    </aside>

    <aside>
    💡 각 컨테이너마다 알고리즘을 구현하는 것이 좋으므로 generic function을 사용하지 않는 것이 좋다. → 템플릿으로 만드는것 x

    </aside>

- 다음은 표준 출력에 한 줄씩 표시해야 하는 정보에 대한 몇 가지 추가 지침이다.
    - 첫 번째 줄에는 명시적 텍스트를 표시한 다음 정렬되지 않은 양의 정수 시퀀스를 표시해야 한다.
    - 두 번째 줄에는 명시적 텍스트와 정렬된 양의 정수 시퀀스를 표시해야 한다.
    - 세 번째 줄에는 양의 정수 시퀀스를 정렬하는데 사용된 첫 번째 컨테이너를 지정하여 알고리즘에서 사용한 시간을 나타내는 명시적 텍스트를 표시해야 한다.
    - 마지막 줄에는 양의 정수 시퀀스를 정렬하는 데 사용된 두 번째 컨테이너를 지정하여 알고리즘에서 사용한 시간을 나타내는 명시적 텍스트를 표시한다.

    <aside>
    ℹ️ 정렬을 수행하는 데 사용된 시간을 표시하는 형식은 자유이지만, 선택한 정밀도는(precision) 사용된 두 컨테이너의 차이를 명확하게 볼 수 있어야 한다.

    </aside>

    - 사용 예시:

    ```bash
    $> ./PmergeMe 3 5 9 7 4 
    Before: 35974
    After: 34579
    Time to process a range of 5 elements with std::[..] : 0.00031 us
    Time to process a range of 5 elements with std::[..] : 0.00014 us 
    $> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
    Before: 141 79 526 321 [...] 
    After: 79 141 321 526 [...]
    Time to process a range of 3000 elements with std::[..] : 62.14389 us 
    Time to process a range of 3000 elements with std::[..] : 69.27212 us 
    $> ./PmergeMe "-1" "2"
    Error
    $> # For OSX USER:
    $> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '` 
    [...]
    $>
    ```

    <aside>
    💡 이 예제에서는 시간 표시가 일부러 이상하게 되어 있다. 물론 정렬 부분과 데이터 관리 부분 모두 모든 작업을 수행하는데 사용된 시간을 표시해야 한다.

    </aside>

    <aside>
    ❗ 경고: 이전 문제에서 사용된 컨테이너 사용은 금지되어 있다.

    </aside>

    <aside>
    ℹ️ 중복과 관련된 오류 관리는 당신의 재량

    </aside>
