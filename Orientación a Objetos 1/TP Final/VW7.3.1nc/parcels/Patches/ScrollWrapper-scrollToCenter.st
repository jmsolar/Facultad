<?xml version="1.0"?>

<st-source>
<time-stamp>From VisualWorks® NonCommercial, 7.3.1 of April 20, 2005 on September 11, 2009 at 8:20:38 am</time-stamp>


<methods>
<class-id>UI.ScrollWrapper</class-id> <category>scrolling</category>

<body package="Interface-Support" selector="scrollToCenter">scrollToCenter
	| coordinate |
	coordinate := self scrollableExtent / 2 
				- ((self scrollableExtent - self visibleExtent) / 2).
	self
		scroll: ((coordinate x / 2) @ coordinate y)negated</body>
</methods>

</st-source>
