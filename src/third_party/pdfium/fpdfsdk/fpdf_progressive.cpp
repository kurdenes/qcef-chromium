// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "public/fpdf_progressive.h"

#include <utility>

#include "core/fpdfapi/cpdf_pagerendercontext.h"
#include "core/fpdfapi/page/cpdf_page.h"
#include "core/fpdfapi/render/cpdf_progressiverenderer.h"
#include "core/fxcrt/fx_memory.h"
#include "core/fxge/cfx_defaultrenderdevice.h"
#include "core/fxge/cfx_renderdevice.h"
#include "fpdfsdk/fsdk_define.h"
#include "fpdfsdk/fsdk_pauseadapter.h"
#include "public/fpdfview.h"
#include "third_party/base/ptr_util.h"

// These checks are here because core/ and public/ cannot depend on each other.
static_assert(CPDF_ProgressiveRenderer::Ready == FPDF_RENDER_READER,
              "CPDF_ProgressiveRenderer::Ready value mismatch");
static_assert(CPDF_ProgressiveRenderer::ToBeContinued ==
                  FPDF_RENDER_TOBECOUNTINUED,
              "CPDF_ProgressiveRenderer::ToBeContinued value mismatch");
static_assert(CPDF_ProgressiveRenderer::Done == FPDF_RENDER_DONE,
              "CPDF_ProgressiveRenderer::Done value mismatch");
static_assert(CPDF_ProgressiveRenderer::Failed == FPDF_RENDER_FAILED,
              "CPDF_ProgressiveRenderer::Failed value mismatch");

DLLEXPORT int STDCALL FPDF_RenderPageBitmap_Start(FPDF_BITMAP bitmap,
                                                  FPDF_PAGE page,
                                                  int start_x,
                                                  int start_y,
                                                  int size_x,
                                                  int size_y,
                                                  int rotate,
                                                  int flags,
                                                  IFSDK_PAUSE* pause) {
  if (!bitmap || !pause || pause->version != 1)
    return FPDF_RENDER_FAILED;

  CPDF_Page* pPage = CPDFPageFromFPDFPage(page);
  if (!pPage)
    return FPDF_RENDER_FAILED;

  auto pOwnedContext = pdfium::MakeUnique<CPDF_PageRenderContext>();
  CPDF_PageRenderContext* pContext = pOwnedContext.get();
  pPage->SetRenderContext(std::move(pOwnedContext));

  CFX_RetainPtr<CFX_DIBitmap> pBitmap(CFXBitmapFromFPDFBitmap(bitmap));
  auto pOwnedDevice = pdfium::MakeUnique<CFX_DefaultRenderDevice>();
  CFX_DefaultRenderDevice* pDevice = pOwnedDevice.get();
  pContext->m_pDevice = std::move(pOwnedDevice);
  pDevice->Attach(pBitmap, !!(flags & FPDF_REVERSE_BYTE_ORDER), nullptr, false);

  IFSDK_PAUSE_Adapter IPauseAdapter(pause);
  FPDF_RenderPage_Retail(pContext, page, start_x, start_y, size_x, size_y,
                         rotate, flags, false, &IPauseAdapter);

  if (pContext->m_pRenderer) {
    return CPDF_ProgressiveRenderer::ToFPDFStatus(
        pContext->m_pRenderer->GetStatus());
  }
  return FPDF_RENDER_FAILED;
}

DLLEXPORT int STDCALL FPDF_RenderPage_Continue(FPDF_PAGE page,
                                               IFSDK_PAUSE* pause) {
  if (!pause || pause->version != 1)
    return FPDF_RENDER_FAILED;

  CPDF_Page* pPage = CPDFPageFromFPDFPage(page);
  if (!pPage)
    return FPDF_RENDER_FAILED;

  CPDF_PageRenderContext* pContext = pPage->GetRenderContext();
  if (pContext && pContext->m_pRenderer) {
    IFSDK_PAUSE_Adapter IPauseAdapter(pause);
    pContext->m_pRenderer->Continue(&IPauseAdapter);
    return CPDF_ProgressiveRenderer::ToFPDFStatus(
        pContext->m_pRenderer->GetStatus());
  }
  return FPDF_RENDER_FAILED;
}

DLLEXPORT void STDCALL FPDF_RenderPage_Close(FPDF_PAGE page) {
  CPDF_Page* pPage = CPDFPageFromFPDFPage(page);
  if (!pPage)
    return;

  CPDF_PageRenderContext* pContext = pPage->GetRenderContext();
  if (!pContext)
    return;

  pContext->m_pDevice->RestoreState(false);
  pPage->SetRenderContext(nullptr);
}
