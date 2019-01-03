<?xml version="1.0"?>

<st-source>
<time-stamp>From VisualWorks® NonCommercial, 7.3.1 of April 20, 2005 on September 11, 2009 at 8:20:22 am</time-stamp>


<methods>
<class-id>RobotApplication</class-id> <category>interface opening</category>

<body package="Robot - Primera Practica" selector="postOpenWith:">postOpenWith: aBuilder

	super postOpenWith: aBuilder.
	(self builder componentAt: #InspectorSubcanvas) widget
							client: self inspector
							spec: #windowSpec
							builder: builder newSubBuilder.
	self worldView container scrollToCenter.
	self refreshInspector.</body>
</methods>

</st-source>
