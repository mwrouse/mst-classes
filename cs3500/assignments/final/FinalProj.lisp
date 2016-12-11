; Program......: Final Project
; File.........: FinalProj.lisp
; Student......: Michael Rouse
; Student ID...: 
; Class........: Comp Sci 3500
; Instructor...: Morales
; Date.........: 2016-12-16
; Description..: Final Program in LISP



; Function.....: myLast
; Parameters...: L - a list
; Description..: Evaluates to the last member of a list
(defun myLast (L)
	; Check if the tail end of the list is nil
	(if (eq (cdr L) nil)
		; Tail is nil
		(car L) ; Return the head of the list (last member of list)

		; Tail is not nil
		(myLast (cdr L)) ; Recursive function call using the tail of the list
	)
)


; Function.....: myCount
; Parameters...: X - element to look for in L
; 							 L - the list to search
; Description..: Evaluates to the number of occurences X in L
(defun myCount (X L)
	; Check if the list is nil
	(if (eq L nil)
		0 ; List is nil, evaluate to 0

		; List is not nill, check for X
		(if (eq (car L) X)
			; Head of L is X
			(+ 1 (myCount X (cdr L))) ; Return +1 and recursively call function

			; Head is not L
			(+ 0 (myCount X (cdr L))) ; Return +0 and recursively call function
		)
	)
)


; Function.....: myGen
; Parameters...: X - integer
;								 Y - integer
; Description..: Evaluates to list of increasing numbers between X and L
(defun myGen (X Y)
	; Check to see if X > Y
	(if (> X Y)
		; X > Y
		nil ; Return an empty list

		; Y >= X (check if equal)
		(if (eq X Y)
			; X = Y
			(cons X nil) ; Add X as the last integer in the list, no more recursion

			; X < Y
			(cons X (myGen (+ 1 X) Y)) ; Add X to the list and recursive call incrementing X
		 )
	)
)


; Function.....: myMember
; Parameters...: X - element to search the list for
;								 L - the list to search
; Description..: Evalutes to true if X is in L
(defun myMember (X L)
	; Check if L is nil
	(if (eq L nil)
		; L = ()
		nil ; False

		; Check for X in L
		(if (eq X (car L))
			; X is head of L
			't ; True

			; X is not head - keep looking
			(myMember X (cdr L))
		)
	)
)


; Function.....: nyCommon
; Parameters...: L1 - First List
;								 L2 - Second list
; Description..: Evalutes to a list of elements that are in both L1 and L2,
;								 advances through L1 looking for the head of L1 in L2
(defun myCommon (L1 L2)
	; Check if L1 is nil
	(if (eq L1 nil)
		; L1 = nil
		nil

		; L1 <> nil, check if L2 is nil
		(if (eq L2 nil)
			; L2 = nil
			nil

			; L2 <> nil, check if head of L1 is in L2
			(if (myMember (car L1) L2)
				; Head of L1 is in L2
				(cons (car L1) (myCommon (cdr L1) L2)) ; Recursive call with tail of L1

				; Head of L1 is no in L2
				(myCommon (cdr L1) L2) ; Proceed through L1
			)
		)
	)
)


; Function.....: myMap
; Parameters...: F - Function
;								 L - List to apply function to
; Description..: Evaluates to list which result is apply F to every member of L
(defun myMap (F L)
	; Check if list is nil
	(if (eq L nil)
		; L is empty
		nil

		; L is not empty
		(cons (funcall F (car L)) (myMap F (cdr L))) ; Add result of F on head of L, and recursively call
	)
)


; Function.....: myReduce
; Parameters...: F - Function
;								 L - List
; Description..: Evaluates to result of applying aggregate function F to every element in L
(defun myReduce (F L)
	; Check if l is nil
	(if (eq L nil)
		; L is nil
		0

		; L is not empty, check if this it he last member
		(if (eq (cdr L) nil)
			; Last member
			(car L)

			; Not last member - add result of F and recursively call with tail of tail of L
			(+ (funcall F (car L) (car (cdr L))) (myReduce F (cdr (cdr L))) )
		)
	)
)
