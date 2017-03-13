Adrian only needed 3 more points to pass, while I needed more.  Thus, Adrian made minor edits and helped with
a helper function.  I did the rest.

I tried to make the heuristic function as good as I possible could, since we could now get minimax to work properly.
(My attempt actually made the AI perform worse against SimplePlayer and ConstantTimePlayer, so I undid it.)
I used multipliers on the heuristic score in order to encourage and discourage the AI to make certain moves.
Corners were optimal, edges were good, and spaces giving access to corners and edges weren't good.  However,
it was a bit buggy and the AI only defeated SimplePlayer about 3/4 of the time.  I then modified the heuristic function
such that the multipliers only affected the AI's piece count.  This caused it to defeat SimplePlayer and ConstantTime-
Player more consistently.  It now defeats SimplePlayer more than 90% of the time and ConstantTimePlayer more than
70% of the time.  Because of this, I don't think the AI will do terribly in the tournament... assuming nothing catastrophic
happens out of nowhere.