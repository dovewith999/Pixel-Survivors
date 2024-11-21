#include "stdafx.h"
#include "..\Public\Bullet.h"


CBullet::CBullet(LPDIRECT3DDEVICE9 _GraphicDevice)
	: CGameObject(_GraphicDevice)
{
}

CBullet::CBullet(const CBullet & rhs)
	: CGameObject(rhs)
{
}

HRESULT CBullet::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBullet::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	//m_pTransformCom->Turn180(D3DXVECTOR3(0.f, 1.f, 0.f));
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(3.f, 3.f, 7.f));

	//Set_WeaponInfo();

	m_tagWeaponStats.szName = L"Bullet";
	m_tagWeaponStats.iAttackDmg = 15;
	m_tagWeaponStats.eWeaponType = WEAPONSTATS::WEAPON_BULLET;

	/*Set_TurnAngle(D3DXVECTOR3(0.f, 1.f, 0.f), 90.f);
	Set_TurnAngle(D3DXVECTOR3(1.f, 0.f, 0.f), 30.f);*/

	return S_OK;
}

void CBullet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return;

	Safe_AddRef(pGameInstance);

	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, );

	if (m_pMasterCube != nullptr)
		m_pMasterCube->Set_Positon(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	Safe_Release(pGameInstance);
}

void CBullet::Late_Tick(_float fTimeDelta)
{
	if (nullptr == m_pRendererCom)
		return;

	__super::Late_Tick(fTimeDelta);

	//__super::Affected_By_Gravity(m_pTransformCom, fTimeDelta);

	//State_Motion();
}

HRESULT CBullet::Render()
{
	if (nullptr == m_pGraphic_Device)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBullet::Render_Cube()
{
	CGameInstance*	pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return E_FAIL;

	Safe_AddRef(pGameInstance);

	//����� �� ť�� ����

	if (nullptr != m_pMasterCube)
	{
		m_pMasterCube->Set_Dead();
	}

	HANDLE		hFile = CreateFile(L"../../Data/Bullet.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	ReadFile(hFile, &MasterCubeSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);
	ReadFile(hFile, &AllCubeSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);
	ReadFile(hFile, &AllVertexPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
	ReadFile(hFile, &CubeCount, sizeof(int), &dwByte, nullptr);

	cout << "ť�� ���� : " << CubeCount << endl;

	if (FAILED(pGameInstance->Add_Layer(LEVEL_GAMEPLAY, L"Layer_MasterCube", L"Prototype_GameObject_MasterCube", MasterCubeSize)))
		return E_FAIL;


	m_pMasterCube = dynamic_cast<CMasterCube*>(pGameInstance->Find_LayerObject(LEVEL_GAMEPLAY, L"Layer_MasterCube"));

	m_pMasterCube->Set_BindTransform(m_pTransformCom);

	for (int ti = 0; ti < CubeCount; ++ti)
	{
		ReadFile(hFile, &eCube, sizeof(CUBE), &dwByte, nullptr);
		ReadFile(hFile, &iIndex, sizeof(int), &dwByte, nullptr);

		if (FAILED(pGameInstance->Add_Layer(LEVEL_GAMEPLAY, L"Layer_Cube", L"Prototype_GameObject_Cube", &eCube)))
			return E_FAIL;;

		m_pCube = dynamic_cast<CCube*>(pGameInstance->Find_LayerObject(LEVEL_GAMEPLAY, L"Layer_Cube"));
		m_pMasterCube->Add_Cube(iIndex, eCube.vSize, m_pCube);
		m_pCube->Set_Position(m_pMasterCube->Get_Position());
	}
	m_pMasterCube->Set_CubeSize(AllCubeSize);
	m_pMasterCube->Set_VertexPos(AllVertexPos);

	//this->Set_TurnAngle(D3DXVECTOR3(0.f, 1.f, 0.f), 60.f);
	//this->Set_TurnAngle(D3DXVECTOR3(1.f, 0.f, 0.f), 60.f);
	m_pMasterCube->Set_CubeSize(D3DXVECTOR3(0.015f, 0.015f, 0.015f));

	//if (m_tagWeaponStats.eWeaponType == WEAPONSTATS::WEAPON_SPEAR)
	//	m_pMasterCube->Set_CubeSize(D3DXVECTOR3(0.015f, 0.015f, 0.015f));
	//else
	//{
	//	m_pMasterCube->Set_CubeSize(AllCubeSize);
	//	m_pMasterCube->Set_CubeSize(D3DXVECTOR3(0.4f, 0.4f, 0.07f));
	//}

	CloseHandle(hFile);

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CBullet::SetUp_Components()
{
	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.f);
	if (FAILED(__super::Add_Components(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Components(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), TEXT("Com_VIBuffer"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Renderer `*/
	if (FAILED(__super::Add_Components(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CBullet::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CBullet::Release_RenderState()
{
	if (nullptr == m_pGraphic_Device)
	{
		return E_FAIL;
	}

	return S_OK;
}

CBullet * CBullet::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBullet* pInstance = new CBullet(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX(TEXT("Error : Failed Created Bullet Prototype"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBullet::Clone(void * pArg)
{
	CBullet* pInstance = new CBullet(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX(TEXT("Error : Failed Cloned Bullet Copy"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBullet::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pVIBufferCom);
}