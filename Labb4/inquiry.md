#### What did you learn from this assignment?
I learned how to implement polymorphism and how to handle private/protected data.

#### What was most difficult to do in this assignment?
Understanding WTF to do

#### The code relies on virtual functions. Could the code have been written without virtual functions?
I think so. I could have made each piece its own class. But then i would have to have a switch-case when itterating trough all the peices. This was amuch more elegant solution.

#### Could ChessPiece have been an abstract class?
Yes, and it amoast is. There is no reason to have the base of chessPiece as there is no "default" chessPiece. Ig a good designchoice would have been to have the pawn as the default piece, then pawn promotion would make more since.

#### There was no separate unit test for each function in this assignment, instead you tested several functions at once with different boards. What are the benefits and drawbacks for this kind of testing compared to unit tests?
The benefits are that the tests are much easier to implement and run.<br>
The drawbacks are as the labblydelse says that some wrongs cancel out, and when you encounter an error or wrong you need to follow it back to the source.

#### What is the problem with a diamond inheritance?
Diamond inheritance lead to amugiety in the inheteted base class.

#### Did you encounter any problem with protected member variables and, if so, how did you solve them?
I often needed the states of onoter piece to find capturing moves, but the color was protected and inacceccable. I solved it by writing public accessor functions.

#### Create a queen object and try to set the unnecessaryInt in ChessPiece. What happens?
Nothing special, Queen only gets the uneccesary int from chessPiece and gets only t´gets the functions from Rook and Bishop.

#### Think about if it would be better if the queen had a bishop and a rook (as members) instead of inherited from them?

Idk what this means