#pragma once
#include "afxwin.h"
#include "frameStorage.h"

// DlgViewEdit dialog

class DlgViewEdit : public CDialogEx
{
	DECLARE_DYNAMIC(DlgViewEdit)

public:
	DlgViewEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgViewEdit();

// Dialog Data
	enum { IDD = IDD_DIALOG_TAB_Edit };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void resetCombox();
	void updateCombox();
	XnSkeletonJoint getCombox(int i);
	void setCombox(int i, XnSkeletonJoint en);

	

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnLbnSelchangeListFrameEdit();	
	afx_msg void OnLbnSelchangeListFrameChecks();
	afx_msg void OnBnClickedBtnSaveCheck();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();

public:
	CListBox _edit_frames;
	CListBox _frame_checks;
	CHECKDEGREES _degrees;
	CComboBox _combo_[3];

};
