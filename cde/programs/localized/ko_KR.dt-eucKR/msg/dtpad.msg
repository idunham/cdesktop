$ $XConsortium: dtpad.msg /main/4 1995/12/08 09:35:45 rswiston $
$ *************************************<+>*************************************
$ *****************************************************************************
$ **
$ **  File:        dtpad.msg
$ **
$ **  Project:     DT Text Editor client (sometimes called dtpad)
$ **
$ **  Description:
$ **  -----------
$ **  This file is the source for the message catalog for dtpad
$ **
$ **
$ *****************************************************************************
$ **
$ **     (c) Copyright 1992, 1993 Hewlett-Packard Company
$ **     All Rights reserved
$ **
$ **
$ *****************************************************************************
$ **
$ *****************************************************************************
$ **  (c) Copyright 1993, 1994 Hewlett-Packard Company
$ **  (c) Copyright 1993, 1994 International Business Machines Corp.
$ **  (c) Copyright 1993, 1994 Sun Microsystems, Inc.
$ **  (c) Copyright 1993, 1994 Novell, Inc.
$ *****************************************************************************
$ **

$set 2
$ **********************************************
$ **  General messages used in multiple files **
$ **********************************************

$ Label used for all "Help" buttons in all DIALOGS.
$ It is not used for the Help menu.
1 ����


$set 4
$ *****************************************************************
$ **                                                    fileCB.c **
$ ** These are the strings which change between the Open dialog  **
$ ** and the Include dialog.  These two operations use the same  **
$ ** Motif dialog, and simply change these two labels.           **
$ *****************************************************************

$ Title of the Open dialog
1 ���� ����

$ label for the File text field in the file selection box
$ ***UNUSED*** This label is no longer used and need not be localized.
2 ������ ����:

$ Title of the Include dialog
3 ���� ����

$ Label for the File text field in the file selection box
$ ***UNUSED*** This label is no longer used and need not be localized.
4 ������ ����:

$ Error when printing a file and a temporary copy can not be saved.
5 �ӽ� ������ ���� �� �����ϴ�.


$set 5
$ ***************************************************************************
$ **                                                               dtpad.c **
$ **                                                             fileDlg.c **
$ **                                                                       **
$ ** Messages and strings used in dialogs for all operations involving the **
$ ** "File" menu items.                                                    **
$ ***************************************************************************
$ These compose the dialog which appears if the user attempts to exit, open
$ a different file, drop a file, or start a "New" session with unsaved
$ changes to the current file.

$ This is used to build: "Save changes to FILENAME?"
1 ��������� %s�� �����ϰڽ��ϱ�?

$ This is used as-is, whenever the current file is unnamed.
2 ���� ������ �̸��� �����ϴ�.\n�����ϰڽ��ϱ�?

$ This is used to build a message like "Do you want to save the current
$ copy of FILENAME before you Edit NEWFILENAME?" when a new file is droped
$ on the edit window.
$ ***UNUSED*** Currently, dropped files are INSERTED in the text rather than
$          opened for editing so this message is no longer used and need
$          not be localized.
3 %s�� ���� ���纻��\n%s��(��) �����ϱ� ����\n�����ϰڽ��ϱ�?

$ Used when about to write over an existing file.
$ The "%s" is replaced by the file name.
5 %s ������ �̹� �ֽ��ϴ�.\n�ش� ������ �� ���� ������ �������� ���ľ��ڽ��ϱ�?

$ Title of "file already exists" dialog.  Also used for other "Warning" type
$ dialogs.
6 ���

$ Title of "Save As" dialog.
7 ���̸� ����

$ Labels for add/don't-add newlines radio buttons in the Save As dialog
8 �ٳ��� ���� ���� �ٹٲ� ���ڰ� �߰���
9 �ٹٲ� ���ڰ� �߰����� ����. [Return]���� ���е� �ٹٲ޸�\n�����˴ϴ�.

$ Labels for the Save Warning dialog. Also used in the confirmation, or
$ Editor Return dialog.
14 �ƴϿ�
15 ��
$ Title of the dialog - used when user selects "New", "Open", or "Exit" with
$ unsaved changes in the text.
16 ����?

$ Title of general error dialog
17 ����

$ Title of the resource-specified "confirmation" dialog
$ This dialog is generally specified by programs such as mailers, which
$ want to know if the user wants to send the message.
$ There is no default message for the dialog, since it is _only_ posted if
$ the message string is specified via a resource (dtpad*confirmationString:)
$ This message is only used if the "dtpad*mainTitle:" resource is not set.
$ If this resource _is_ set, the the mainTitle is also used as the title
$ for the exit confirmation dialog.
$ DO NOT LOCALIZE - the user should never see this message
18 Exit Confirmation

$ Title for general information dialog. e.g. Find dialog can't find word in
$ file.
20 ����

$ Default file name in Save As dialog box.
21 UNTITLED

$ Error message when a file can not be saved.  The "%1$s" gets replaced by
$ the file name and the "%2$s" gets replaced by the reason why the file could
$ not be saved (messages 31-39).
30 %1$s��(��) ������ �� �����ϴ�.\n%2$s

$ Messages 31-39 are reasons why a file could not be saved.
$ Messages 34-39 are substitued in message 30 for "%2$s".
31 ������ ������ �� �����ϴ�.\n���� �̸��� �������� �ʾҽ��ϴ�.

34 �ƹ����Ե� ���Ͽ� ���� ���� ������ �����ϴ�.

35 ������ ������ ���丮�Դϴ�.

36 ������ ������ Ư�� ���� ��ġ�Դϴ�.

37 ������ ������ ���� ��� ��ġ�Դϴ�.

$ ***UNUSED*** This message should never appear since currently there is
$          only one supported file format - text.  And this type is
$          hard coded into dtpad.
38 ��ȿ���� ���� ���� ����

$ This is a "catch all" when the file can not be saved and none of the above
$ errors apply.
39 ������ �� �� ���� - ��ũ ������ ������ �Ͱ����ϴ�.

$ This is displayed when a ToolTalk edit request on a buffer is received,
$ a Save operation is done and there are unsaved changes.
40 ��������� �����ϰڽ��ϱ�?

$ This is displayed when a ToolTalk edit request on a file or buffer is
$ received with a document name specified in the request, a Save operation
$ is done and there are unsaved changes.  The "%s" in the message is
$ replaced by the document name (instead of the filename).
41 ��������� "%s"�� �����ϰڽ��ϱ�?

$ Title of "Copy As" dialog which is substitued for the "Save As" dialog
$ when file name changes are disallowd.  This should match the menu button
$ label specified in message 108 of set 11.
42 ���̸����� �����ϱ�

$ Title of "Copy To File" dialog which is substitued for the "Save As" dialog
$ when file name changes are disallowd.  This should match the menu button
$ label specified in message 110 of set 11.
43 ���Ϸ� �����ϱ�

$ Labels for add/don't-add newlines radio buttons in the SaveAs and Save dialogs
44 �ٸ��߱� ���� ���� �ٹٲ� ���ڸ� �߰��Ͻʽÿ�.
45 �ٹٲ� ���ڸ� �߰����� ���ʽÿ�. [Return]�� ���� ������� �� �и����� \n�����˴ϴ�.
$
$ New message as of 5/31/95 (i.e. new since Sample Implementation). This
$ new message is in response to bug DTS CISlx19530.
$
46 ���Ͽ� ���Ⱑ ������ �ʰų�\n������ ��ο� �����ϴ�.


$set 6
$ ************************************************************************
$ **                                                           fileIo.c **
$ **                                                                    **
$ ** Error messages generated when there are problems reading a file.   **
$ ************************************************************************

1 �� ������ �б� �������� ���Ƚ��ϴ�.
2 �� ������ �����ϴ�.
3 ���丮�� ������ �� �����ϴ�.
4 Ư�� ���� ��ġ ������ ������ �� �����ϴ�.
5 ���� ��� ��ġ ������ ������ �� �����ϴ�.
6 ���Ե� null ���ڵ��� ���Ͽ��� �и��Ǿ����ϴ�.
7 ������ �ε��� �� �����ϴ�. (�޸� ����)
8 ������ ����� �� �����ϴ�. (���¸� �� �� ����)
9 ������ ���� �� �����ϴ�. (�б� ����?)

$ Message placed in the status line message area based on the -viewOnly
$ resource and whether or not the file being edited is read only
10 ���� ����
11 �б� ����


$set 7
$ ************************************
$ **                         main.c **
$ **                        dtpad.c **
$ ** Prefix string for all dialogs. **
$ ************************************
$ bogus?? blank string gotten but otherwise unused in main()
$ DO NOT LOCALIZE string 1
1 

$ The name used in the title bar of every window.
$ Be sure to end this message with a space character.
2 ���� ������ - 

$ Default file name used in the main window title.
$ ***UNUSED*** This mesage has been replaced by message 6 of this set and
$          need not be localized.
3 (�̸�����)

$ Terminal error message displayed to stdout when the desk top services
$ can not be initialized (via DtInitialize())
4 ����Ʈž ���񽺸� �ʱ�ȭ�� �� �����ϴ� ... ���� �����⸦ ��ġ�� ���Դϴ�.

$ Terminal error message displayed to stdout when a connection to the
$ display can not be opend (via XtDisplay())
5 ���÷��̸� �� �� �����ϴ� ... ���� �����⸦ ��ġ�� ���Դϴ�.

$ Default file name used in the main window title.
$ This should correspond to the default file name used in the "Save As"
$ dialog box - specified in message 21 of set 5.
6 (�̸�����)
$
$ New messages (7,8) since CDE/SI - error gets displayed when user tries to run
$ dtpad -server when and dtpad server process is already running on the
$ $DISPLAY.
7 ����: dtpad ������ %s����\n\
�� ���÷��̸� ���� ���񽺸� �ϰ� �ֽ��ϴ�.
8 ����: dtpad ������ �� ���÷��̸�\n\
���� ���񽺸� �ϰ� �ֽ��ϴ�.
$
$ Message 9 is also new since CDE/SI - new as of 5/22/95.  It is a usage message
$ for dtpad. Don't translate the '-OPTION' just the text explaining the
$ option.
$
9 '%s' is a bad option.\n\
����: %s...\n\
   -saveOnClose\n\
\tDtpad�� ���� �����⸦ ���� �� ������� ���� ������\n\
\t�ڵ����� ��ȭ���� �����մϴ�.\n\n\
   -missingFileWarning\n\
\t������ ������ �� �� ������ ���ų� ����� �� ���� ��쿡\n\
\t��� ��ȭ ���ڸ� ��Ÿ���ϴ�.\n\n\
   -noReadOnlyWarning\n\
\t������ ������ ��, �� ���Ͽ� ���� ���� ������ ������,\n\
\t��Ÿ�� ��� ��ȭ ���ڸ� ��Ȱ��ȭ��ŵ�ϴ�.\n\n\
   -noNameChange\n\
\t�о��� ���ϰ� �ٸ� �̸����� ������ ������ ��\n\
\t���� ������ ������ �⺻ ���� �̸��� ��������\n\
\t�ʽ��ϴ�.\n\n\
   -viewOnly\n\
\t���� �����쿡�� ������ ������ ������� �ʽ��ϴ�.\n\
\t���� ������� ���� ������� �۵��ϰ� �˴ϴ�.\n\n\
   -statusLine\n\
\t���� �������� �Ʒ��ʿ� ���� ���� ǥ���մϴ�.\n\
\t���� ���� ���� ���� Ŀ���� �ִ� ���� �� ��ȣ��\n\
\t�����ݴϴ�.\n\n\
   -wrapToFit\n\
\t�ʱ⿡ �ٸ��� ��带 �մϴ�.\n\n\
   -workspaceList WorkspaceList\n\
\t������ �۾��� �Ǵ� �۾���鿡 ���� ������\n\
\t�������� ���� ȣ�⿡ ���� ���� �����찡\n\
\t��Ÿ���ϴ�.\n\n\
   -session SessionFile\n

10 \t���� �������� ��� ���� ������� ���� CDE ����\n\
\t���� ����Ǵ� ������ �����մϴ�. �� ���û����� \n\
\t�����Ǹ� ���� ������Ʈ�� �ٸ� ���û��׵��� ���\n\
\t���õ˴ϴ�.\n\n\
   -standAlone\n\
\t���� �������� ���� ȣ���� ���� ������ ������\n\
\t������ ��ü�� ������� ���� ó���� �����ϰ�\n\
\t�մϴ�.\n\n\
   -noBlocking\n\
\t���� ������ ������ ��û���� ���� �䱸�� ó����\n\
\t�� ������ �ٷ� ���� ������ ��û�� ó����\n\
\t�����մϴ�.\n\n\
   -server\n\
\t���� ���������� ������ ���� ������ ������\n\
\t���÷��̿� ��� �μ� ���� �䱸�� ó���ϵ���\n\
\t�����մϴ�.\n\n\
   -exitOnLastClose\n\
\t���� ������ ���� ���μ����� ���÷�����\n\
\t������ ���� �����츦 ���� �� �����ŵ�ϴ�.\n\
\t�� ���û����� ���� ���μ������� ����ǹǷ�\n\
\t-server ���û��װ� �Բ��� ���˴ϴ�.\n\n\
���û��׿� ���� �ڼ��� ������ dtpad �¶��� �������� �����Ͻʽÿ�.
$

$set 10
$ ************************************************************************
$ **                                                          session.c **
$ ** THESE MESSAGES ARE _ONLY_ WRITTEN TO THE ERRORLOG FILE.
$ **
$ ************************************************************************
$ Strings used to build error messages issued when the session save
$ file cannot be read or written.
1 ���� ��� ������ �����Ͻʽÿ�.
2  %s��(��) ������ �����ϴ� �� ����� �����Դϴ�.


$set 11
$ ***********************************************************
$ **                                              dtpad.c **
$ **                                                       **
$ ** These are all of the menu button labels and mnemonics **
$ ***********************************************************

$ ***UNUSED***     Messages 1-14 are no longer used and need not be localized.
$          All of the mnemonics and labels relating to the "Help" menu
$          have been replaced by messages 81-96.

$ *
$ * Mnemonics and labels for the "Help" pulldown menu and items.
$ *
$ Mnemonic and label for the "Help" pulldown menu
1 H
2 ����H

$ mnemonic and label for the "Overview" item
3 V
4 ����V...

$ mnemonic and label for the "Tasks" item
5 T
6 �۾�T...

$ nmemonic and label for the "Table of Contents" item are message nos. 71 & 72

$ mnemonic and label for the "Reference" item
7 R
8 ����R...

$ mnemonic and label for the "On Item" item
9 O
10 �׸�O

$ mnemonic and label for "Using Help" item
11 U
12 ���� ���U...

$ mnemonic and label for "About Text Editor" item
13 A
14 ���� �����⿡ ���Ͽ�A...

$ *
$ * Mnemonics and labels for the "File" pulldown menu and items.
$ *
$ mnemonic and label for the "File" pulldown menu
15 F
16 ����F

$ mnemonic and label for the "New" item
17 N
18 �� ����N

$ mnemonic and label for the "Open" item
19 O
20 ����O...

$ mnemonic and label for the "Include" item
21 I
22 ����I...

$ mnemonic and label for the "Save" item
$ NOTE: The "Save" label can be either Message 24 or message 73
23 S
24 ����S

$ mnemonic and label for the "Save As" item
25 A
26 ���̸� ����A...

$ mnemonic and label for the "Print" item
27 P
28 �μ�P...

$ mnemonic and label for the "Close" item
29 C
30 �ݱ�C

$ *
$ * Mnemonics and labels for the "Edit" pulldown menu and items.
$ *
$ mnemonic and label for the "Edit" pulldown menu
31 E
32 ����E

$ mnemonic and label for the "Undo" menu item
33 U
34 �������U

$ mnemonic and label for the "Cut" menu item
35 t
36 �ڸ���t

$ mnemonic and label for the "Copy" menu item
37 C
38 �����ϱ�C

$ mnemonic and label for the "Paste" menu item
39 P
40 ���̱�P

$ mnemonic and label for the "Clear" menu item
41 e
42 �ٽ��Է�e

$ mnemonic and label for the "Delete" menu item
43 D
44 ���ֱ�D

$ ***UNUSED*** Messages 45-50 are no longer used and need not be localized.
$          They have been replaced by messages 101-106 of this set.
$ mnemonic and label for the "Select All" menu item
$ 45 A
$ 46 Select All

$ mnemonic and label for the "Find/Change" menu item
$ 47 F
$ 48 Find/Change...

$ mnemonic and label for the Check Spelling menu item
$ 49 S
$ 50 Check Spelling...

$ *
$ * Mnemonics and labels for the "Format" pulldown menu and items.
$ *
$ mnemonic and label for the "Format" pulldown menu
51 r
52 ����r

$ mnemonic and label for the "Settings..." menu item
53 S
54 ������S...

$ mnemonic and label for the "Paragraph" menu item
55 P
56 ����P

$ mnemonic and label for the "All" menu item
57 l
58 ��ül

$ *
$ * Mnemonics and labels for the "Options" pulldown menu and items.
$ *
$ mnemonic and label for the "Format" pulldown menu
59 O
60 ���û���O

$ mnemonic and label for the "Overstrike" toggle button
61 O
62 ���ľ���O 

$ mnemonic and label for the "Word Wrap" toggle button
$ ***UNUSED***  This label and mnemonic are no longer used and need not be
$               localized.  They've been replaced by messages 111 and 112.
63 W
64 �ٳ�����W

$ mnemonic and label for the "Status Line" toggle button
65 S
66 ���� ǥ��S

$ *
$ * Late additions.
$ *

$ nmemonic and label for the "Table of Contents" item of the "Help" menu
$ ***UNUSED***     This nmemonic and label are no longer used and need not be
$          localized.  They've been replaced by messages 87 and 88.
71 C
72 ����C...

$ label for the "Save" item in the "File" pulldown menu
$ NOTE: This label is used in place of message 24 when text has been
$       changed but has not been saved
73 ����(�ʿ�)S


$ *
$ * Mnemonics and labels for the "Help" pulldown menu and items.
$ *
$ Mnemonic and label for the "Help" pulldown menu
81 H
82 ����H

$ mnemonic and label for the "Overview" item
83 v
84 ����v

$ mnemonic and label for the "Tasks" item
85 T
86 �۾�T

$ nmemonic and label for the "Table of Contents" item
87 C
88 ����C

$ mnemonic and label for the "Reference" item
89 R
90 ����R

$ mnemonic and label for the "On Item" item
91 O
92 �׸�O

$ mnemonic and label for "Using Help" item
93 U
94 ���� ���U

$ mnemonic and label for "About Text Editor" item
95 A
96 ���� �����⿡ ���Ͽ�A


$ *
$ * Changes for "Edit" pulldown menu messages 45-50.
$ *

$ mnemonic and label for the "Select All" menu item
101 S
102 ��ü ����S

$ mnemonic and label for the "Find/Change" menu item
103 F
104 ã��/�ٲٱ�F...

$ mnemonic and label for the Check Spelling menu item
105 k
106 ö�� �˻�k...

$ mnemonic and label for the "Copy As" File menu item
$ (should match the dialog title specified in message 42 of set 5)
$ ***UNUSED***  This label is no longer used and need not be localized.
107 A
108 ���̸����� �����ϱ�...

$ mnemonic and label for the "Copy To File" File menu item
$ (should match the dialog title specified in message 42 of set 5)
109 F
110 ���Ϸ� �����ϱ�F...

$ mnemonic and label for the "Wrap To Fit" toggle button
111 W
112 �ٸ��߱�W


$ ***********************************************************
$ **                                              helpCB.c **
$ **                                                       **
$ ** Messages and strings associated with online help.     **
$ **                                                       **
$ ***********************************************************
$set 12
$ Message used for "Help - On Item" if the user clicks outside application
1 ���� �����⳻�� �׸��� �����ؾ� �մϴ�.


$ ***********************************************************
$ **                                        ttMsgSupport.c **
$ **                                                       **
$ ** Messages and strings associated with ToolTalk.        **
$ **                                                       **
$ ***********************************************************
$set 13
1 �˻���(checkpoint) ������ �����߽��ϴ�.
2 �˻���(checkpoint) ������ �����߽��ϴ�.

$ NEW message after the SAMPLE IMPLEMENTATION.... more errors/warnings can
$ be detected while reading in a file via ToolTalk.
3 Unable to set contents of Text Editor (unknown reason).