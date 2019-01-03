SUnit 3.1 Release Candidate Notes
Dialect: VisualWorks
Current Release Candidate level: 4
Last Update: 20030322
==================================

Changes:
RC4 - 20030322
* Changed TestCase class>>#isAbstract to call #sunitName
* Changed TestCase>>#failureLog to call SUnitNameResolver class>>#defaultLogDevice

RC3 - 20030320
* Corrected TestResult>>#tests. Probably irrelevant, since there are not senders.
* Changed TestCase class>>#version to #sunitVersion because of a clash with ST/X

RC2 - 20030318
* Removed TestResult class var <ExFailure>. Probably irrelevant, since not referenced

RC1 - 20030320
* First release candidate. See http://ansi-st-tests.sourceforge.net/news.htm for 
details.