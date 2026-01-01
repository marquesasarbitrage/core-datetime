# CORE-DATETIME

**CORE-DATETIME** is a **C++17 date and time library** designed for **financial and quantitative applications**.  
It provides robust, well-defined abstractions for civil dates, timestamps, time intervals, and industry-standard financial conventions.

---

## Library Structure

The library is organized into the following components:

### 1. Datetime Toolbox
A collection of **pure functions** for civil date and timestamp arithmetic, including:
- Leap-year logic
- Date offsets and differences
- Calendar-aware calculations

This layer contains **no stateful objects** and serves as the mathematical foundation of the library.

---

### 2. TimeDelta
An object representing a **duration of time**, supporting:
- Days, hours, minutes, seconds
- Arithmetic operations
- Safe interaction with `Datetime`

Used to express time intervals independently of calendar context.

---

### 3. Datetime
The core object representing a **point in time**, expressed as:
- A civil date
- A timestamp

Features include:
- Comparison operators
- Arithmetic with `TimeDelta`
- Conversion between civil and timestamp representations

---

### 4. Day Count Conventions
Financial utilities for computing **year fractions** between two `Datetime` objects according to standard conventions such as:
- ACT/ACT (ISDA, ICMA)
- ACT/360
- ACT/365
- 30/360

This module is essential for pricing, accruals, and interest calculations.

---

### 5. Business Day Conventions
Calendar-aware date adjustment tools supporting:
- Holiday calendars
- Business-day adjustment rules (Following, Modified Following, Preceding, etc.)

Designed for cash-flow scheduling and settlement logic.

---

### 6. Datetime Sequences
A high-level abstraction for navigating ordered date collections:
- Forward and backward iteration
- Sub-sequences by index or date range
- Schedule generation

Useful for coupon schedules, fixing dates, and time series traversal.

---

## Design Goals

- C++17 compliant
- Deterministic and explicit date logic
- Financial-grade correctness
- Minimal dependencies
- Performance-oriented

---

This README file has been reviewed and edited with assistance from ChatGPT.