#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"
#include "Timer.h"
#include <array>

CScene::CScene(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

CScene::~CScene()
{
}

// 3d ���� ��ư�� ����� ���� �Լ�
void make_start(CCubeMesh* mesh, CGameObject** obj, int num, float x, float y) {
	CText* pText = new CText();
	pText->SetMesh(mesh);
	pText->SetColor(RGB(255, 125, 0));
	pText->SetPosition(x, y, 40.0f);
	obj[num] = pText;
}

void CScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 200.0f;
	CWallMesh* pWallCubeMesh = new CWallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 30);

	m_pWallsObject = new CWallsObject();
	m_pWallsObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pWallsObject->SetMesh(pWallCubeMesh);
	m_pWallsObject->SetColor(RGB(0, 0, 0));
	m_pWallsObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
	m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);
	m_pWallsObject->m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.05f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));


	// ť�� -> ������ ��ü
	CAirplaneMesh* pAirplaneMesh = new CAirplaneMesh(6.0f, 6.0f, 1.0f);

	m_nObjects = 2;
	m_ppObjects = new CGameObject * [m_nObjects];

	CExplosiveObject *pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pAirplaneMesh);
	pExplosiveObject->SetColor(RGB(255, 0, 0));
	pExplosiveObject->SetPosition(40.0f, 0.0f, 40.0f);
	pExplosiveObject->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	pExplosiveObject->SetMovingSpeed(10.5f);
	pExplosiveObject->Rotate(90.0f, 190.0f);
	m_ppObjects[0] = pExplosiveObject;


	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pAirplaneMesh);
	pExplosiveObject->SetColor(RGB(255, 0, 0));
	pExplosiveObject->SetPosition(-40.0f, -10.0f, 40.0f);
	pExplosiveObject->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	pExplosiveObject->SetMovingSpeed(10.5f);
	pExplosiveObject->Rotate(90.0f, 190.0f);
	m_ppObjects[1] = pExplosiveObject;


	// �ǵ� �߰�
	CCubeMesh* cShieldMesh= new CCubeMesh(6.5f, 6.5f, 6.5f);

	m_pShield = new CShield;
	m_pShield->SetMesh(cShieldMesh);
	m_pShield->SetColor(RGB(0, 255, 0)); 
	m_pShield->SetPosition(0.0, 0.0, 0.0);

	// ���۹�ư �߰�
	CCubeMesh* cTextMesh = new CCubeMesh(1.0, 1.0, 1.0);
	#define size 76  // �迭 ũ��
	m_nText = size;
	m_ppText = new CGameObject * [m_nText];
	// ���۹�ư ��ġ �迭
	std::array<float, size> x_list = {
		///// S
		-23.0,
		-22.0,
		-21.0,
		-20.0,
		//
		-23.0,
		-23.0,
		-23.0,
		-23.0,
		//
		-22.0,
		-21.0,
		-20.0,
		//
		-20.0,
		-20.0,
		-20.0,
		//
		-21.0,
		-22.0,
		-23.0,


		///// T
		-18.0,
		-17.0,
		-16.0,
		-15.0,
		-14.0,
		//
		-16.0,
		-16.0,
		-16.0,
		-16.0,
		-16.0,
		-16.0,


		////// A
		-12.0,
		-11.0,
		-10.0,
		-9.0,
		//
		-12.0,
		-12.0,
		-12.0,
		-12.0,
		-12.0,
		-12.0,
		//
		-9.0,
		-9.0,
		-9.0,
		-9.0,
		-9.0,
		-9.0,
		//
		-11.0,
		-10.0,
		//


		//////R
		-7.0,
		-7.0,
		-7.0,
		-7.0,
		-7.0,
		-7.0,
		-7.0,
		//
		-6.0,
		-5.0,
		-4.0,
		//
		-3.0,
		-3.0,
		-4.0,
		//
		-5.0,
		-6.0,
		-7.0,
		//
		-3.0,
		-3.0,
		-3.0,
		//


		//////T
		-1.0,
		0.0,
		1.0,
		2.0,
		3.0,
		//
		1.0,
		1.0,
		1.0,
		1.0,
		1.0,
		1.0,
		//
	};

	std::array<float, size> y_list = { 
		///// S
		15.0,
		15.0,
		15.0,
		15.0,
		//
		14.0,
		13.0,
		12.0,
		//
		12.0,
		12.0,
		12.0,
		12.0,
		//
		11.0,
		10.0,
		9.0,
		//
		9.0,
		9.0,
		9.0,


		///// T
		15.0,
		15.0,
		15.0,
		15.0,
		15.0,
		//
		14.0,
		13.0,
		12.0,
		11.0,
		10.0,
		9.0,
		//


		////// A
		14.0,
		15.0,
		15.0,
		14.0,
		//
		14.0,
		13.0,
		12.0,
		11.0,
		10.0,
		9.0,
		//
		14.0,
		13.0,
		12.0,
		11.0,
		10.0,
		9.0,
		//
		12.0,
		12.0,
		//


		//////R
		15.0,
		14.0,
		13.0,
		12.0,
		11.0,
		10.0,
		9.0,
		//
		15.0,
		15.0,
		15.0,
		//
		14.0,
		13.0,
		12.0,
		//
		12.0,
		12.0,
		12.0,
		//
		11.0,
		10.0,
		9.0,
		//


		//////T
		15.0,
		15.0,
		15.0,
		15.0,
		15.0,
		//
		14.0,
		13.0,
		12.0,
		11.0,
		10.0,
		9.0,
		//
	};

	for (int i = 0; i < m_nText; ++i)
		make_start(cTextMesh, m_ppText, i, x_list[i] + 9.0, y_list[i] - 5.0);


#ifdef _WITH_DRAW_AXIS
	m_pWorldAxis = new CGameObject();
	CAxisMesh* pAxisMesh = new CAxisMesh(0.5f, 0.5f, 0.5f);
	m_pWorldAxis->SetMesh(pAxisMesh);
#endif
}

void CScene::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();

	for (int i = 0; i < m_nObjects; i++) if (m_ppObjects[i]) delete m_ppObjects[i];
	if (m_ppObjects) delete[] m_ppObjects;

	if (m_pWallsObject) delete m_pWallsObject;

#ifdef _WITH_DRAW_AXIS
	if (m_pWorldAxis) delete m_pWorldAxis;
#endif
}

void CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1':
		case '2':
		/*case '3': // ��ü�� �����Ƿ� ��Ȱ��ȭ
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':*/
		{
			CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[int(wParam - '1')];
			pExplosiveObject->m_bBlowingUp = true;
			break;
		}
		case 'A':
			for (int i = 0; i < m_nObjects; i++)
			{
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

CGameObject* CScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{
	XMFLOAT3 xmf3PickPosition;
	xmf3PickPosition.x = (((2.0f * xClient) / (float)pCamera->m_Viewport.m_nWidth) - 1) / pCamera->m_xmf4x4PerspectiveProject._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / (float)pCamera->m_Viewport.m_nHeight) - 1) / pCamera->m_xmf4x4PerspectiveProject._22;
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);
	XMMATRIX xmmtxView = XMLoadFloat4x4(&pCamera->m_xmf4x4View);

	int nIntersected = 0;
	float fNearestHitDistance = FLT_MAX;
	CGameObject* pNearestObject = NULL;

	// �߰� �� ����
	if (!m_pPlayer->game_start) {
		for (int i = 0; i < m_nText; i++)
		{
			float fHitDistance = FLT_MAX;
			nIntersected = m_ppText[i]->PickObjectByRayIntersection(xmvPickPosition, xmmtxView, &fHitDistance);
			if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance))
			{
				fNearestHitDistance = fHitDistance;
				pNearestObject = m_ppText[i];
			}
		}

	}
	else {
		for (int i = 0; i < m_nObjects; i++)
		{
			float fHitDistance = FLT_MAX;
			nIntersected = m_ppObjects[i]->PickObjectByRayIntersection(xmvPickPosition, xmmtxView, &fHitDistance);
			if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance))
			{
				fNearestHitDistance = fHitDistance;
				pNearestObject = m_ppObjects[i];
			}

		}
	}
	
	return(pNearestObject);
}

void CScene::CheckObjectByObjectCollisions()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
			{
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];
			}
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}

void CScene::CheckObjectByWallCollisions()
{
	for (int i = 0; i < m_nObjects; i++)
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);
		switch (containType)
		{
		case DISJOINT:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}
}


void CScene::CheckPlayerByWallCollision()
{
	BoundingOrientedBox xmOOBBPlayerMoveCheck;
	m_pWallsObject->m_xmOOBBPlayerMoveCheck.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&m_pWallsObject->m_xmf4x4World));
	XMStoreFloat4(&xmOOBBPlayerMoveCheck.Orientation, XMQuaternionNormalize(XMLoadFloat4(&xmOOBBPlayerMoveCheck.Orientation)));

	if (!xmOOBBPlayerMoveCheck.Intersects(m_pPlayer->m_xmOOBB)) m_pWallsObject->SetPosition(m_pPlayer->m_xmf3Position);
}


void CScene::CheckObjectByBulletCollisions()
{
	CBulletObject** ppBullets = ((CAirplanePlayer*)m_pPlayer)->m_ppBullets;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = 0; j < BULLETS; j++)
		{
			if (ppBullets[j]->m_bActive && m_ppObjects[i]->m_xmOOBB.Intersects(ppBullets[j]->m_xmOOBB))
			{
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
				ppBullets[j]->Reset();
			}
		}
	}
}


// �÷��̾� �⵿���� �߰�
void CScene::CheckPlayerByBulletCollisions()
{
	for (int i = 0; i < m_nObjects; ++i)
	{
	CBulletObject** ppBullets = ((CExplosiveObject*)m_ppObjects[i])->m_ppBullets;

		for (int j = 0; j < BULLETS; j++)
		{
			if (ppBullets[j]->m_bActive && m_pPlayer->m_xmOOBB.Intersects(ppBullets[j]->m_xmOOBB))
			{
				// ���尡 Ȱ��ȭ �� ���¿����� ������ ü���� 20 ��������, �׷��� �ʴٸ� �÷��̾��� ü���� 10 ��������
				if (m_pPlayer->shield_state) {
					if(m_pShield->shield_hp > 0)
						m_pShield->shield_hp -= 20;

					// ������ ü���� ������ �������� ���� ���°� �����ȴ�.
					if (m_pShield->shield_hp <= 0) {
						m_pPlayer->shield_state = false;
						m_pShield->shield_hp = 255;
					}
				}

				if (!m_pPlayer->shield_state) {
					if (m_pPlayer->player_hp > 0) {
						m_pPlayer->player_hp -= 20;
						m_pPlayer->SetColor(RGB(0.0, 0.0, m_pPlayer->player_hp));
					}

					// �÷��̾ ������ ���� �����Ǿ� �ʱ� ��ġ�� �ǵ��� ����.
					if (m_pPlayer->player_hp <= 0) {
						m_pPlayer->player_hp = 255;
						m_pShield->shield_hp = 255;


						m_pPlayer->SetPosition(0.0, 0.0, 0.0);

						for(int i = 0; i < BULLETS; ++i)
							ppBullets[i]->Reset();
						m_pPlayer->game_start = false;
					}
				}

				ppBullets[j]->Reset();
			}
		}
	}
}


void CScene::Animate(float fElapsedTime)
{
	m_pWallsObject->Animate(fElapsedTime);

	// ���ӽ��� �߰�
	if (m_pPlayer->game_start)
		for (int i = 0; i < m_nObjects; i++) 
			m_ppObjects[i]->Animate(fElapsedTime);

	// �ǵ� �߰�(false���¶� �Ⱥ���)
	XMFLOAT3 player_position = m_pPlayer->GetPosition();
	m_pShield->SetPosition(player_position.x, player_position.y, player_position.z);
	m_pShield->SetColor(RGB(0.0, m_pShield->shield_hp, 0.0));

	
	CheckPlayerByWallCollision();

	CheckObjectByWallCollisions();

	CheckObjectByObjectCollisions();

	CheckObjectByBulletCollisions();

	// �÷��̾� �浹 ���� �߰�
	CheckPlayerByBulletCollisions();
	
	// �߰�
	if (m_pPlayer->game_start) {
		for (int i = 0; i < m_nObjects; i++) {
			((CExplosiveObject*)m_ppObjects[i])->delay += fElapsedTime * 60;

			if (((CExplosiveObject*)m_ppObjects[i])->delay > 120 + i*10) {
					
				((CExplosiveObject*)m_ppObjects[i])->FireBullet(m_pPlayer);

				((CExplosiveObject*)m_ppObjects[i])->delay = 0;
			}
		}
	}
}

void CScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);
	m_pWallsObject->Render(hDCFrameBuffer, pCamera);

	// ����ȭ��
	if (!m_pPlayer->game_start)
		for (int i = 0; i < m_nText; ++i) {
			m_ppText[i]->Render(hDCFrameBuffer, pCamera);
		}
	// �÷��� ȭ��
	else {
		for (int i = 0; i < m_nObjects; i++)
			m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
	}

	if (m_pPlayer) {
		m_pPlayer->Render(hDCFrameBuffer, pCamera);
		// �÷��̾��� ���尡 Ȱ��ȭ �Ǿ��������� ������ �Ѵ�
		if(m_pPlayer->shield_state)
			m_pShield->Render(hDCFrameBuffer, pCamera);
	}

	

//UI
#ifdef _WITH_DRAW_AXIS
	CGraphicsPipeline::SetViewOrthographicProjectTransform(&pCamera->m_xmf4x4ViewOrthographicProject);
	m_pWorldAxis->SetRotationTransform(&m_pPlayer->m_xmf4x4World);
	m_pWorldAxis->Render(hDCFrameBuffer, pCamera);
#endif
}
